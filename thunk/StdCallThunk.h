
#ifndef STD_CALL_THUNK_H
#define STD_CALL_THUNK_H

#include <Windows.h>

namespace ghost{

#if defined(_M_IX86)
	void* __stdcall AllocStdCallThunk(void);
	void  __stdcall FreeStdCallThunk(void*);

#pragma pack(push, 1)
	class StdCallThunk_{
		DWORD mov_;         // mov dword ptr [esp+0x4], this_ (esp+0x4就是第一个参数)
		DWORD this_;        //
		BYTE jmp_;          // jmp proc
		DWORD relproc_;     // relative jmp

	public:
		bool Init(DWORD_PTR proc, void* pThis)
		{
			mov_ = 0x042444C7;  //C7 44 24 0C
			this_ = PtrToUlong(pThis);
			jmp_ = 0xe9;
			relproc_ = DWORD((INT_PTR)proc - ((INT_PTR)this+sizeof(StdCallThunk_)));
			// 用自身更新指令缓存
			return ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(StdCallThunk_)) ? true : false;
		}
		// 某些thunk将动态的为代码分配内存
		void* GetCodeAddress()
		{
			return this;
		}
		void* operator new(size_t)
		{
			return AllocStdCallThunk();
		}
		void operator delete(void* pThunk)
		{
			FreeStdCallThunk(pThunk);
		}
	};
#pragma pack(pop)

#elif defined(_M_AMD64)
	void* AllocStdCallThunk(void);
	void  FreeStdCallThunk(void*);
#pragma pack(push, 2)
	class StdCallThunk_{
		USHORT rcxMov_;         // mov rcx, pThis
		ULONG64 rcxImm_;        // 
		USHORT raxMov_;         // mov rax, target
		ULONG64 raxImm_;        //
		USHORT raxJmp_;         // jmp target

	public:
		bool Init(DWORD_PTR proc, void *pThis)
		{
			rcxMov_ = 0xb948;          // mov rcx, pThis
			rcxImm_ = (ULONG64)pThis;  // 
			raxMov_ = 0xb848;          // mov rax, target
			raxImm_ = (ULONG64)proc;   //
			raxJmp_ = 0xe0ff;          // jmp rax
			return ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(StdCallThunk_)) ? true : false;
		}
		void* GetCodeAddress()
		{
			return this;
		}
		void* operator new(size_t)
		{
			return AllocStdCallThunk();
		}
		void operator delete(void* pThunk)
		{
			FreeStdCallThunk(pThunk);
		}
	};
#pragma pack(pop)
#elif defined (_M_ALPHA)
#pragma pack(push,4)
	struct StdCallThunk_{
		DWORD ldah_at_;      //  ldah    at, HIWORD(func)
		DWORD ldah_a0_;      //  ldah    a0, HIWORD(this)
		DWORD lda_at_;       //  lda     at, LOWORD(func)(at)
		DWORD lda_a0_;       //  lda     a0, LOWORD(this)(a0)
		DWORD jmp_;          //  jmp     zero,(at),0

	public:
		bool Init(DWORD_PTR proc, void* pThis)
		{
			ldah_at_ = (0x279f0000 | HIWORD(proc)) + (LOWORD(proc)>>15);
			ldah_a0_ = (0x261f0000 | HIWORD(pThis)) + (LOWORD(pThis)>>15);
			lda_at_ = 0x239c0000 | LOWORD(proc);
			lda_a0_ = 0x22100000 | LOWORD(pThis);
			jmp_ = 0x6bfc0000;
			return ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(StdCallThunk_)) ? true : false;
		}
		void* GetCodeAddress()
		{
			return this;
		}
	};
#pragma pack(pop)
#elif defined(_SH3_)
#pragma pack(push,4)
	struct StdCallThunk_{
		WORD mov_r0_;		// mov.l	pFunc,r0
		WORD mov_r1_;		// mov.l	pThis,r1
		WORD jmp_;			// jmp		@r0
		WORD nop_;			// nop
		DWORD pFunc_;
		DWORD pThis_;

	public:
		bool Init(DWORD_PTR proc, void* pThis)
		{
			mov_r0_ = 0xd001;
			mov_r1_ = 0xd402;
			jmp_ = 0x402b;
			nop_ = 0x0009;
			pFunc_ = (DWORD)proc;
			pThis_ = (DWORD)pThis;
			return ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(StdCallThunk_)) ? true : false;
		}
		void* GetCodeAddress()
		{
			return this;
		}
	};
#pragma pack(pop)
#elif defined(_MIPS_)
#pragma pack(push,4)
	struct StdCallThunk_{
		WORD pFuncHi_;
		WORD lui_t0_;		// lui		t0,PFUNC_HIGH
		WORD pFuncLo_;
		WORD ori_t0_;		// ori		t0,t0,PFUNC_LOW
		WORD pThisHi_;
		WORD lui_a0_;		// lui		a0,PTHIS_HIGH
		DWORD jr_t0_;		// jr		t0
		WORD pThisLo_;
		WORD ori_a0_;		// ori		a0,PTHIS_LOW

	public:
		bool Init(DWORD_PTR proc, void* pThis)
		{
			pFuncHi_ = HIWORD(proc);
			lui_t0_  = 0x3c08;
			pFuncLo_ = LOWORD(proc);
			ori_t0_  = 0x3508;
			pThisHi_ = HIWORD(pThis);
			lui_a0_  = 0x3c04;
			jr_t0_   = 0x01000008;
			pThisLo_ = LOWORD(pThis);
			ori_a0_  = 0x3484;
			return ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(StdCallThunk_)) ? true : false;
		}
		void* GetCodeAddress()
		{
			return this;
		}
	};
#pragma pack(pop)
#elif defined(_ARM_)
#pragma pack(push,4)
	struct StdCallThunk_{
		DWORD mov_r0_;		// mov	r0, pThis
		DWORD mov_pc_;		// mov	pc, pFunc
		DWORD pThis_;
		DWORD pFunc_;

	public:
		bool Init(DWORD_PTR proc, void* pThis)
		{
			mov_r0_ = 0xE59F0000;
			mov_pc_ = 0xE59FF000;
			pThis_ = (DWORD)pThis;
			pFunc_ = (DWORD)proc;
			return ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(StdCallThunk_)) ? true : false;
		}
		void* GetCodeAddress()
		{
			return this;
		}
	};
#pragma pack(pop)
#elif defined(_M_IA64)
#pragma pack(push,8)
	extern "C" void StdCallThunkProcProc(void);
	struct _FuncDesc{
		void* pfn;
		void* gp;
	};
	struct StdCallThunk_{
		_FuncDesc funcdesc_;
		void* pFunc_;
		void* pThis_;

	public:
		bool Init(DWORD_PTR proc, void* pThis)
		{
			funcdesc_.pfn = ((_FuncDesc*)(&StdCallThunkProcProc))->pfn;
			funcdesc_.gp = &pFunc_;
			pFunc_ = reinterpret_cast< void* >(proc);
			pThis_ = pThis;
			return ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(StdCallThunk_)) ? true : false;
		}
		void* GetCodeAddress()
		{
			return( &m_funcdesc );
		}
	};
#pragma pack(pop)

#else
#error Only ARM, ALPHA, SH3, MIPS, IA64, AMD64 and X86 supported
#endif

#if defined(_M_IX86) || defined (_M_AMD64)

#pragma pack(push, 8)
	class DynamicStdCallThunk{
		StdCallThunk_* pThunk_;

	public:
		DynamicStdCallThunk() : pThunk_(0){}
		~DynamicStdCallThunk()
		{
			if (pThunk_)
			{
				delete pThunk_;
				pThunk_ = 0;
			}
		}

	private:
		DynamicStdCallThunk(const DynamicStdCallThunk&);
		DynamicStdCallThunk& operator =(const DynamicStdCallThunk&);

	public:
		bool Init(DWORD_PTR proc, void* pThis)
		{
			if (!pThunk_) 
			{
				pThunk_ = new StdCallThunk_;
				if (!pThunk_)
				{
					return false;
				}
			}
			return pThunk_->Init(proc, pThis);
		}

		void* GetCodeAddress()
		{
			return pThunk_->GetCodeAddress();
		}
	};

#pragma pack(pop)
	typedef DynamicStdCallThunk StdCallThunk;
#else
	typedef StdCallThunk_ StdCallThunk;
#endif  // _M_IX86 || _M_AMD64

} // namespace ghost

#endif // STD_CALL_THUNK_H