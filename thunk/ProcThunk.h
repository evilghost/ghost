
#ifndef PROC_THUNK_H
#define PROC_THUNK_H

#include "StdCallThunk.h"

namespace ghost{

	template<typename T>
	class ProcThunk{
	public:
		typedef T ProcType;

	private:
		StdCallThunk thunk_;

	public:
		bool Init(ProcType proc, void* pThis)
		{
			return thunk_.Init((DWORD_PTR)proc, pThis);
		}
		ProcType GetPROC()
		{
			return (ProcType)thunk_.GetCodeAddress();
		}
	};

	namespace window{

		// 窗口过程thunk
		typedef ghost::ProcThunk<WNDPROC> ProcThunk;

	} // namespace window

	namespace timer{

		// 定时器过程thunk
		typedef ghost::ProcThunk<TIMERPROC> ProcThunk;

	} // namespace timer

} // namespace ghost

#endif // PROC_THUNK_H