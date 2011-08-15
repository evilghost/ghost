
#include "StdCallThunk.h"

extern "C"
{
	typedef struct _CLIENT_ID {
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID;
	typedef CLIENT_ID *PCLIENT_ID;

	struct _PEB;
	typedef struct _PEB * PPEB;

	typedef struct _TEB {
		NT_TIB NtTib;
		PVOID EnvironmentPointer;
		CLIENT_ID ClientId;
		PVOID ActiveRpcHandle;
		PVOID ThreadLocalStoragePointer;
		PPEB ProcessEnvironmentBlock;
		/* ....*/
	} TEB, *PTEB;

	_inline struct _TEB * _NtCurrentTeb(void) {__asm mov eax, fs:[0x18]}

}

namespace ghost{

#if !defined(_X86_)
#error Unsupported platform
#endif

#if !defined(PAGE_SIZE)
#define PAGE_SIZE 4096
#endif

#if !defined(DECLSPEC_NOINLINE)
#define DECLSPEC_NOINLINE __declspec(noinline)
#endif

#define THUNKS_PER_PAGE (PAGE_SIZE / sizeof(THUNK_ENTRY))

	BOOL static InitializeThunkPool_(VOID);

	typedef PSINGLE_LIST_ENTRY (__stdcall *PINTERLOCKED_PUSH_ENTRY_SLIST)(
		PSLIST_HEADER,PSINGLE_LIST_ENTRY ListEntry);

	typedef PSINGLE_LIST_ENTRY (__stdcall *PINTERLOCKED_POP_ENTRY_SLIST)(
		PSLIST_HEADER);

	typedef union _THUNK_ENTRY{
		SLIST_ENTRY SListEntry;
		ghost::StdCallThunk_ Thunk;
	}THUNK_ENTRY, *PTHUNK_ENTRY;

	PSLIST_HEADER g_thunkPool = NULL;

#define THUNK_USE_HEAP_VALUE (PSLIST_HEADER)UlongToPtr(1)
#define THUNK_USE_HEAP()     (g_thunkPool == THUNK_USE_HEAP_VALUE)

	PINTERLOCKED_PUSH_ENTRY_SLIST g_FuncInterlockedPushEntrySList = NULL;
	PINTERLOCKED_POP_ENTRY_SLIST  g_FuncInterlockedPopEntrySList = NULL;

	void* AllocStdCallThunk_cmn(void)
	{
		PTHUNK_ENTRY lastThunkEntry;
		PTHUNK_ENTRY thunkEntry;
		PVOID thunkPage;

		if (NULL == g_thunkPool) 
		{
			if (!InitializeThunkPool_()) 
			{
				return 0;
			}
		}

		if (THUNK_USE_HEAP()) 
		{
			thunkEntry = (PTHUNK_ENTRY)::HeapAlloc(
				::GetProcessHeap(), 0,
				sizeof(ghost::StdCallThunk_));
			if (NULL == thunkEntry) 
			{
				return 0;
			}
			return thunkEntry;
		}

		thunkEntry = (PTHUNK_ENTRY)g_FuncInterlockedPopEntrySList(g_thunkPool);
		if (NULL != thunkEntry) 
		{
			return &thunkEntry->Thunk;
		}

		thunkPage = (PTHUNK_ENTRY)::VirtualAlloc(
			NULL, PAGE_SIZE, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (NULL == thunkPage) {
			return 0;
		}

		*(DWORD volatile *)thunkPage;
		thunkEntry = (PTHUNK_ENTRY)g_FuncInterlockedPopEntrySList(g_thunkPool);
		if (NULL != thunkEntry) 
		{
			::VirtualFree(thunkPage, 0, MEM_RELEASE);
			return thunkEntry;
		}

		thunkEntry = (PTHUNK_ENTRY)thunkPage;
		lastThunkEntry = thunkEntry + THUNKS_PER_PAGE - 1;
		do {
			g_FuncInterlockedPushEntrySList(g_thunkPool,&thunkEntry->SListEntry);
			thunkEntry += 1;
		} while (thunkEntry < lastThunkEntry);

		return thunkEntry;
	}

	void FreeStdCallThunk_cmn (void* pThunk)
	{
		PTHUNK_ENTRY thunkEntry;

		if (THUNK_USE_HEAP()) 
		{
			::HeapFree(::GetProcessHeap(), 0, pThunk);
		} 
		else 
		{
			thunkEntry = (PTHUNK_ENTRY)pThunk;
			g_FuncInterlockedPushEntrySList(g_thunkPool,&thunkEntry->SListEntry);
		}
	}

	static BOOL DECLSPEC_NOINLINE InitializeThunkPool_(VOID)
	{
#define PEB_POINTER_OFFSET 0x34

		BOOL result = ::IsProcessorFeaturePresent(12/*PF_NX_ENABLED*/);
		if (result == FALSE) 
		{
			g_thunkPool = THUNK_USE_HEAP_VALUE;
			return TRUE;
		}

		HMODULE kernel32Module = ::LoadLibrary(TEXT("kernel32.dll"));
		if (kernel32Module != NULL) {

			g_FuncInterlockedPushEntrySList = (PINTERLOCKED_PUSH_ENTRY_SLIST)
				::GetProcAddress(kernel32Module, "InterlockedPushEntrySList" );

			g_FuncInterlockedPopEntrySList = (PINTERLOCKED_POP_ENTRY_SLIST)
				::GetProcAddress(kernel32Module, "InterlockedPopEntrySList" );
		}

		if (g_FuncInterlockedPushEntrySList == NULL 
			|| g_FuncInterlockedPopEntrySList == NULL) 
		{
			return FALSE;
		}

		PSLIST_HEADER* ThunkPoolPtr = (PSLIST_HEADER *)((PCHAR)(_NtCurrentTeb()->ProcessEnvironmentBlock) + PEB_POINTER_OFFSET);

		PSLIST_HEADER ThunkPool = *ThunkPoolPtr;
		if (NULL == ThunkPool) 
		{
			ThunkPool = (PSLIST_HEADER)::HeapAlloc( 
				::GetProcessHeap(), 0, sizeof(SLIST_HEADER));
			if (NULL == ThunkPool) 
			{
				return FALSE;
			}

			//InitializeSListHead(atlThunkPool);
			ThunkPool->Alignment = 0;

			if (::InterlockedCompareExchangePointer( 
				(PVOID *)ThunkPoolPtr,ThunkPool,NULL) != NULL) 
			{
				::HeapFree(::GetProcessHeap(), 0, ThunkPool);
			}
			ThunkPool = *ThunkPoolPtr;
		}
		g_thunkPool = ThunkPool;
		return TRUE;
	}

	void* __stdcall AllocStdCallThunk(void)
	{
		return AllocStdCallThunk_cmn();
	}

	void __stdcall FreeStdCallThunk(void* pThunk)
	{
		FreeStdCallThunk_cmn(pThunk);
	}

} // namespace ghost