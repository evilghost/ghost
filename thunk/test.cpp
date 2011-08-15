
#include "test.h"

namespace ghost{

	ATOM RegisterWndClass(
		HINSTANCE hInstance, 
		WNDPROC wndProc, 
		const TCHAR* className)
	{
		assert(className && wndProc);
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(wcex);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= className;
		wcex.hIconSm		= NULL;
		return ::RegisterClassEx(&wcex);
	}

	HWND CreateWnd(
		HINSTANCE hInstance, 
		const TCHAR* className, 
		const TCHAR* title)
	{
		assert(className && title);
		HWND hWnd = ::CreateWindowEx(0, className, title, WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
		return hWnd;
	}

	void ShowWnd(HWND hWnd, int cmdShow)
	{
		assert(::IsWindow(hWnd));
		::ShowWindow(hWnd, cmdShow);
		::UpdateWindow(hWnd);
	}
	int MessageLoop()
	{
		MSG msg = {0};
		while (::GetMessage(&msg, NULL, 0, 0))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		return msg.wParam;
	}

} // namespace ghost

int APIENTRY _tWinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPTSTR /*cmdLine*/,
	int cmdShow)
{
	static const TCHAR* const wndClassName = TEXT("ThunkTestWindow");
	static const TCHAR* const wndTitle = TEXT("ThunkTestWindow");
	ghost::Window testWnd;
	if (!testWnd.Create(hInstance, wndClassName, wndTitle, cmdShow))
	{
		::GetLastError();
		assert(false);
		return EXIT_FAILURE;
	}
	return ghost::MessageLoop();
}