#include "Precompiled.h"

#if defined(EDN_WINDOWS)
#include "Application/Application.h"

using namespace std;
static u32 s_counter = 0;

#define STYLE_WINDOWED (WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE)
#define STYLE_WINDOWED_FIXED (WS_CAPTION | WS_SYSMENU | WS_POPUP | WS_MINIMIZEBOX | WS_VISIBLE)
#define STYLE_BORDERLESS (WS_POPUP | WS_VISIBLE)
#define STYLE_FULLSCREEN (WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)

/*
	ChangeDisplaySettings
	if fullscreen -? SetWindowPos 0, 0
	setwindowlongptr
*/

struct window_size
{
	u32 width, height;
};

window_size get_monitor_size()
{
	return window_size { (u32)GetSystemMetrics(SM_CXSCREEN), (u32)GetSystemMetrics(SM_CYSCREEN) };
}

void center_window(HWND hwnd)
{
	window_size ms = get_monitor_size();
	RECT rc;
	GetWindowRect(hwnd, &rc);

	u32 width = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
	u32 height = (GetSystemMetrics(SM_CXSCREEN) - rc.bottom) / 2;

	MoveWindow(hwnd, (ms.width - (rc.right - rc.left)) / 2, (ms.height - (rc.bottom - rc.top)) / 2,
		rc.right - rc.left, rc.bottom - rc.top, TRUE);
	//SetWindowPos(hwnd, 0, width, height, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

window_size get_center_size(HWND hwnd)
{
	RECT rc;
	window_size size;
	GetWindowRect(hwnd, &rc);

	size.width = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
	size.height = (GetSystemMetrics(SM_CXSCREEN) - rc.bottom) / 2;
	return size;
}

void configWindowSize(HWND hwnd, u32 style, window_size size)
{
	RECT rect;
	rect.right = size.height;
	rect.bottom = size.width;
	AdjustWindowRect(&rect, style, 0);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_FRAMECHANGED);
	SetWindowLongPtr(hwnd, GWL_STYLE, style);
}

LRESULT CALLBACK WindowsEventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	using namespace edn;
	Application * app = reinterpret_cast<Application*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

	switch (msg)
	{
	case WM_CREATE:
		EDN_TODO("Initalize Renderer");
		break;
	case WM_CLOSE:
		app->close();
		break;
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		EDN_TODO("Handle Window resizing");
		break;

	case WM_SYSCOMMAND:
		if (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER)
			return 0;
		break;

	case WM_MOUSEMOVE:
	case WM_MOUSEWHEEL:
		break;

	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case '1': app->setWindowStyle(WindowStyle::EDN_WINDOW_FULLSCREEN); break;
		case '2': app->setWindowStyle(WindowStyle::EDN_WINDOW_WINDOWED); break;
		case '3': app->setWindowStyle(WindowStyle::EDN_WINDOW_WINDOWED_FIXED); break;
		case '4': app->setWindowStyle(WindowStyle::EDN_WINDOW_BORDERLESS); break;
		case '5': app->setWindowStyle(WindowStyle::EDN_WINDOW_BORDERLESS_WINDOW);break;
		}
		break;
	case WM_KEYUP:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

namespace edn
{
	void Application::setupOsWindow()
	{
		hinstance = GetModuleHandle(0);
		classname = title + std::to_string(s_counter);
		s_counter = 0;

		WNDCLASSEX wc{ 0 };
		wc.cbSize = sizeof(wc);
		wc.hInstance = hinstance;
		wc.lpfnWndProc = WindowsEventHandler;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName = classname.c_str();

		if (!RegisterClassEx(&wc))
		{
			cout << "Win32 register window failed" << endl;
			system("pause");
			exit(0);
		}

		DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		RECT wr = { 0, 0, LONG(size.width), LONG(size.height) };
		AdjustWindowRectEx(&wr, style, FALSE, ex_style);
		hwnd = CreateWindowEx(
			0,
			classname.c_str(),
			title.c_str(),
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left,
			wr.bottom - wr.top,
			0,
			0,
			hinstance,
			0);

		if (!hwnd)
		{

		}

		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
		ShowWindow(hwnd, SW_SHOW);
		updateOsWindowStyle();
		SetForegroundWindow(hwnd);
		SetFocus(hwnd);
	}

	void Application::cleanupOsWindow()
	{
		DestroyWindow(hwnd);
		UnregisterClass(classname.c_str(), hinstance);
	}

	void Application::updateOsWindow()
	{
		MSG msg;
		while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Application::updateOsWindowStyle()
	{
		// usefull resource http://stackoverflow.com/a/34465684
		bool success;
		DEVMODE mode = { 0 };
		RECT rect = { 0 };
		s32 w, h;
		if (prev_style != style)
		{
			// If we are something other than windowed then try and get back to that
			if (prev_style == WindowStyle::EDN_WINDOW_FULLSCREEN)
			{
				success = ChangeDisplaySettings(0, 0) == DISP_CHANGE_SUCCESSFUL;

				auto msize = get_monitor_size();

				RECT rect = { 0 };
				rect.right = size.width;
				rect.bottom = size.height;
				SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_WINDOWED);
				AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
				center_window(hwnd);
			}

			if (prev_style == WindowStyle::EDN_WINDOW_BORDERLESS_WINDOW)
			{
				SetWindowPos(hwnd, HWND_TOP, 0, 0, size.width, size.height, SWP_FRAMECHANGED);
				SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_WINDOWED);
				center_window(hwnd);
			}
		}
		else
		{
			if (style == WindowStyle::EDN_WINDOW_WINDOWED)
			{
				SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_WINDOWED);
				center_window(hwnd);
			}
		}

		// Now that we have a base case of a default window we can change it to the current setting
		switch (style)
		{
		case WindowStyle::EDN_WINDOW_FULLSCREEN:
			EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode);
			mode.dmSize = sizeof(DEVMODE);
			mode.dmPelsWidth = size.width;
			mode.dmPelsHeight = size.height;
			mode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

			success = ChangeDisplaySettings(&mode, 0) == DISP_CHANGE_SUCCESSFUL;
			SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_FULLSCREEN);
			break;

		case WindowStyle::EDN_WINDOW_BORDERLESS:
			rect.right = size.width;
			rect.bottom = size.height;
			AdjustWindowRect(&rect, STYLE_BORDERLESS, 0);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_FRAMECHANGED);
			SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_BORDERLESS);
			center_window(hwnd);
			break;

		case WindowStyle::EDN_WINDOW_WINDOWED_FIXED:
			rect.right = size.width;
			rect.bottom = size.height;
			AdjustWindowRect(&rect, STYLE_WINDOWED_FIXED, 0);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_FRAMECHANGED);
			SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_WINDOWED_FIXED);
			center_window(hwnd);
			break;

		case WindowStyle::EDN_WINDOW_BORDERLESS_WINDOW:
			w = GetSystemMetrics(SM_CXSCREEN);
			h = GetSystemMetrics(SM_CYSCREEN);
			SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_BORDERLESS);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
			break;

		case WindowStyle::EDN_WINDOW_WINDOWED:
			rect.right = size.width;
			rect.bottom = size.height;
			AdjustWindowRect(&rect, STYLE_WINDOWED, 0);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_FRAMECHANGED);
			SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_WINDOWED);
			center_window(hwnd);
			return;
		}

	}
}
#endif