
#ifndef TEST_H
#define TEST_H

#include "ProcThunk.h"
#include <tchar.h>
#include <cassert>

namespace ghost{

	ATOM RegisterWndClass(
		HINSTANCE /*hInstance*/, 
		WNDPROC /*wndProc*/, 
		const TCHAR* /*className*/);
	HWND CreateWnd(
		HINSTANCE /*hInstance*/, 
		const TCHAR* /*className*/, 
		const TCHAR* /*title*/);
	void ShowWnd(HWND /*hWnd*/, int /*cmdShow*/);
	int MessageLoop();

	class Window{
		window::ProcThunk thunk_;
		HWND hWnd_;
		WNDPROC originalProc_;

	public:
		Window()
			: hWnd_(NULL)
			, originalProc_(::DefWindowProc)
		{
			thunk_.Init(StartWndProc_, this);
		}
		~Window()
		{
			if (::IsWindow(hWnd_))
			{
				::DestroyWindow(hWnd_);
			}
		}

	public:
		bool Create(
			HINSTANCE hInstance, 
			const TCHAR* className, 
			const TCHAR* title, 
			int cmdShow)
		{
			if (0 == RegisterWndClass(hInstance, ::DefWindowProc, className))
			{
				assert(false);
				return false;
			}
			hWnd_ = CreateWnd(hInstance, className, title);
			if (!::IsWindow(hWnd_))
			{
				assert(false);
				return false;
			}
			originalProc_ = (WNDPROC)::SetWindowLong(hWnd_, GWL_WNDPROC, (LONG)thunk_.GetPROC());
			ShowWnd(hWnd_, cmdShow);
			return true;
		}

	private:
		LRESULT WndProc_(UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_NCDESTROY:
				::PostQuitMessage(EXIT_SUCCESS);
				break;
			case WM_ERASEBKGND:
				break;
			case WM_PAINT:
				{
					PAINTSTRUCT ps = {0};
					::BeginPaint(hWnd_, &ps);

					static const TCHAR* const testText = TEXT("Hello Ghost!");
					::TextOut(ps.hdc, 0, 0, testText, _tcslen(testText));

					::EndPaint(hWnd_, &ps);
				}
				break;
			}
			assert(originalProc_);
			return ::CallWindowProc(originalProc_, hWnd_, message, wParam, lParam);
		}

		static LRESULT CALLBACK StartWndProc_(
			HWND hWnd, 
			UINT message, 
			WPARAM wParam, 
			LPARAM lParam)
		{
			Window* pThis = (Window*)hWnd;
			return pThis->WndProc_(message, wParam, lParam);
		}
	
	};

} // namespace ghost

#endif // TEST_H