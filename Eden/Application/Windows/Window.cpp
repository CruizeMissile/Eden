#include "Precompiled.h"
#include "Window.h"


static int s_counter = 0;
using namespace std;

#define STYLE_WINDOWED (WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE)
#define STYLE_WINDOWED_FIXED (WS_CAPTION | WS_SYSMENU | WS_POPUP | WS_MINIMIZEBOX | WS_VISIBLE)
#define STYLE_BORDERLESS (WS_POPUP | WS_VISIBLE)
#define STYLE_FULLSCREEN (WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)

struct Size
{
	u32 width, height;
};

namespace edn
{
	namespace Win32
	{
		LRESULT CALLBACK WindowsEventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

			switch (msg)
			{
			case WM_CLOSE:
				window->setRunning(false);
				break;
			case WM_KEYUP:
				switch ((char)wParam)
				{
				case '1': window->setWindowStyle(WindowStyle::FULLSCREEN); break;
				case '2': window->setWindowStyle(WindowStyle::WINDOWED); break;
				case '3': window->setWindowStyle(WindowStyle::WINDOWED_FIXED); break;
				case '4': window->setWindowStyle(WindowStyle::BORDERLESS); break;
				case '5': window->setWindowStyle(WindowStyle::BORDERLESS_WINDOWED); break;
				case VK_ESCAPE: window->setRunning(false); break;
				}
				break;
			case WM_QUIT:
				std::cout << "Quiting" << std::endl;
				break;
			default: break;
			}
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		u32 convertWidnowStyle(WindowStyle style)
		{
			switch (style)
			{
			case edn::WindowStyle::FULLSCREEN:          return (u32)STYLE_FULLSCREEN;
			case edn::WindowStyle::WINDOWED:            return (u32)STYLE_WINDOWED;
			case edn::WindowStyle::WINDOWED_FIXED:      return (u32)STYLE_WINDOWED_FIXED;
			case edn::WindowStyle::BORDERLESS:          return (u32)STYLE_BORDERLESS;
			case edn::WindowStyle::BORDERLESS_WINDOWED: return (u32)STYLE_BORDERLESS;
			default:                                    return (u32)STYLE_WINDOWED;
			}
		}

		Size get_monitor_size()
		{
			return Size{ (u32)GetSystemMetrics(SM_CXSCREEN), (u32)GetSystemMetrics(SM_CYSCREEN) };
		}

		void center_window(HWND hwnd)
		{
			u32 ms_width = (u32)GetSystemMetrics(SM_CXSCREEN);
			u32 ms_height = (u32)GetSystemMetrics(SM_CYSCREEN);

			RECT rc;
			GetWindowRect(hwnd, &rc);

			u32 width = rc.right - rc.left;
			u32 height = rc.bottom - rc.top;

			MoveWindow(hwnd,
				(ms_width - width) / 2,
				(ms_height - height) / 2,
				width, height, TRUE
			);
		}

		u8 get_window_frame_height(WindowStyle style)
		{
			switch (style)
			{
			case WindowStyle::WINDOWED:
			case WindowStyle::WINDOWED_FIXED:
				return ((GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER)) * 2) + GetSystemMetrics(SM_CYCAPTION);
				break;
			default: return 0;
			}
		}
		u8 get_window_frame_width(WindowStyle style)
		{
			switch (style)
			{
			case WindowStyle::WINDOWED:
			case WindowStyle::WINDOWED_FIXED:
				return (GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER)) * 2;
				break;
			default: return 0;
			}
		}

		WindowCreateInfo WindowCreateInfo::Default {"Eden Engine", 1024, 576, 0};

		// ------------------------------------------------------------------------------------------------------------
		// Window

		Window::Window(const WindowCreateInfo& info)
		{
			initialize(info);
		}

		void Window::initialize(const WindowCreateInfo& info)
		{
			if (initialized)
			{
				cout << "cannot initialize as the window is already initialized" << endl;
				return;
			}

			title = info.title;
			width = info.width;
			height = info.height;

			// Getting the hinstance from the operating system
			hinstance = GetModuleHandle(0);
			class_name = title + std::to_string(s_counter);

			WNDCLASSEX wc = { 0 };
			wc.cbSize = sizeof(wc);
			wc.hInstance = hinstance;
			wc.lpfnWndProc = WindowsEventHandler;
			wc.hIcon = LoadIcon(0, IDI_APPLICATION);
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wc.lpszClassName = class_name.c_str();

			if (!RegisterClassEx(&wc))
			{
				cout << "[win32] RegisterClassEx() call failed" << endl;
				system("pause");
				exit(0);
			}

			DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			RECT wr = { 0,0,LONG(width), LONG(height) };
			AdjustWindowRectEx(&wr, style, FALSE, ex_style);

			hwnd = CreateWindowEx(
				ex_style,           // ExStyle
				class_name.c_str(), // class name
				title.c_str(),      // window name
				style,              // Regular style
				CW_USEDEFAULT,      // x
				CW_USEDEFAULT,      // y
				wr.right - wr.left, // width
				wr.bottom - wr.top, // height
				0,                  // Window parent
				0,                  // Menu
				hinstance,          // Hinstance
				0                   // lpParam
			);

			if (!hwnd)
			{
				cout << "[win32] CreateWindowEx() failed" << endl;
				system("pause");
				exit(0);
			}

			// Setting the windows long ptr to 'this' pointer so that can get it back
			// in callback functions
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
			center_window(hwnd);
			ShowWindow(hwnd, SW_SHOW);
			SetForegroundWindow(hwnd);
			SetFocus(hwnd);

			initialized = true;
			running = true;
		}

		Window::~Window()
		{
			if (initialized)
				cleanup();
		}

		void Window::cleanup()
		{
			DestroyWindow(hwnd);
			UnregisterClass(class_name.c_str(), hinstance);
			initialized = false;
		}

		void Window::update()
		{
			MSG msg;
			while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		void Window::setWindowStyle(WindowStyle sty)
		{
			if (style == sty)
				return;

			style = sty;
			change_style();
		}

		void Window::show()
		{
			ShowWindow(hwnd, SW_SHOW);
		}

		void Window::change_style()
		{
			// http://stackoverflow.com/a/431548
			bool success;
			DEVMODE mode = { 0 };
			Size size;
			RECT rect{ 0 };
			RECT rcClient, rcWind;
			POINT ptDiff;

			// Since we checked to see if the style is different if it is fullscreen then
			// the new style cannot be fullscreen
			if (fullscreen && !borderless)
			{
				success = ChangeDisplaySettings(0, 0) == DISP_CHANGE_SUCCESSFUL;
				GetClientRect(hwnd, &rcClient);
				GetWindowRect(hwnd, &rcWind);
				ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
				ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;
				MoveWindow(hwnd, rcWind.left, rcWind.top, width + ptDiff.x, height + ptDiff.y, TRUE);
				fullscreen = false;
			}

			switch (style)
			{
			case edn::WindowStyle::FULLSCREEN:
				EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode);
				mode.dmSize = sizeof(DEVMODE);
				mode.dmPelsWidth = width;
				mode.dmPelsHeight = height;
				mode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

				success = ChangeDisplaySettings(&mode, 0) == DISP_CHANGE_SUCCESSFUL;
				SetWindowLongPtr(hwnd, GWL_STYLE, STYLE_FULLSCREEN);
				fullscreen = true;
				borderless = false;
				break;

			case edn::WindowStyle::WINDOWED:
			case edn::WindowStyle::WINDOWED_FIXED:
				rect.right = width + get_window_frame_width(style);
				rect.bottom = height + get_window_frame_height(style);
				SetWindowLongPtr(hwnd, GWL_STYLE, convertWidnowStyle(style));
				SetWindowPos(hwnd, HWND_TOP, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_FRAMECHANGED);
				borderless = false;
				break;

			case edn::WindowStyle::BORDERLESS:
				rect.right = width;
				rect.bottom = height;
				SetWindowLongPtr(hwnd, GWL_STYLE, convertWidnowStyle(style));
				SetWindowPos(hwnd, HWND_TOP, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_FRAMECHANGED);
				break;

			case edn::WindowStyle::BORDERLESS_WINDOWED:
				size = get_monitor_size();
				SetWindowPos(hwnd, HWND_TOP, 0, 0, size.width, size.height, SWP_FRAMECHANGED);
				SetWindowLongPtr(hwnd, GWL_STYLE, convertWidnowStyle(style));
				break;
			}

			if (style == WindowStyle::BORDERLESS || style == WindowStyle::BORDERLESS_WINDOWED)
				borderless = true;

			if (style != WindowStyle::FULLSCREEN)
				center_window(hwnd);
			SetFocus(hwnd);
		}
	}
}
