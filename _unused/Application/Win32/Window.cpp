#include "Precompiled.h"
#include "Window.h"
#include "Application/Application.h"

using namespace std;

#if defined(EDN_WINDOWS)

// This is the HINSTANCE of the application.
extern "C" IMAGE_DOS_HEADER __ImageBase;

#define BITS_PER_PIXEL          32
#define DEPTH_BUFFER_BITS       24
#define STENCIL_BUFFER_BITS     8
#define STYLE_EXTENDED          WS_EX_APPWINDOW

static int s_counter = 0;
static const String s_classname = "Eden";

u32 get_monitor_width();
u32 get_monitor_height();

LONG get_style(bool fullscreen, bool bordered, bool resizable);
RECT get_window_style(LONG style, u32 width, u32 height);
bool apply_fullscreen(HWND hwnd, bool isfullscreen, u32 width, u32 height);
bool apply_style(HWND hwnd, LONG style, u32 width, u32 height);
bool apply_resultion(HWND hwnd, LONG style, u32 width, u32 height);

namespace edn
{
    namespace win32
    {
        Window::Window()
        {
        }

        Window::~Window()
        {
            if (hwnd != NULL)
            {
                if (fullscreen)
                    setFullscreen(false);

                DestroyWindow(hwnd);
                UnregisterClass(s_classname.c_str(), hinstance);
                hwnd = 0;
            }
        }

        void Window::createWindow(const WindowInfo& info)
        {
            if (hwnd != 0)
            {
                cout << "Window is already initialized cannot create!" << endl;
                return;
            }

            title = info.title;
            width = info.width;
            height = info.height;

            // Getting the hinstance from the operating system
            //hinstance = GetModuleHandle(0);
            hinstance = reinterpret_cast<HINSTANCE>(&__ImageBase);
            class_name = title + std::to_string(s_counter);

            WNDCLASSEX wc = { 0 };
            wc.cbSize = sizeof(WNDCLASSEX);
            wc.style = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = Window::WindowsEventHandler;
            wc.hInstance = hinstance;
            wc.hIcon = LoadIcon(0, IDI_APPLICATION);
            wc.hCursor = LoadCursor(0, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
            wc.lpszClassName = s_classname.c_str();
            wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

            if (!RegisterClassEx(&wc))
            {
                cout << "[win32] RegisterClassEx() call failed" << endl;
                system("pause");
                exit(0);
            }

            LONG style = get_style(info.fullscreen, info.bordered, info.resizable);
            RECT wr = get_window_style(style, width, height);

            hwnd = CreateWindowEx(
                STYLE_EXTENDED  ,    // ExStyle
                s_classname.c_str(), // class name
                title.c_str(),       // window name
                style,               // Regular style
                CW_USEDEFAULT,       // x
                CW_USEDEFAULT,       // y
                wr.right - wr.left,  // width
                wr.bottom - wr.top,  // height
                0,                   // Window parent
                0,                   // Menu
                hinstance,           // Hinstance
                0                    // lpParam extra data
            );

            if (hwnd == 0)
            {
                cout << "[win32] CreateWindowEx() failed" << endl;
                system("pause");
                exit(0);
            }

            setFullscreen(info.fullscreen);

            ShowWindow(hwnd, SW_SHOW);
            SetForegroundWindow(hwnd);
        }

        bool Window::setFullscreen(bool isfullscreen)
        {
            if (hwnd != 0)
            {
                if (isfullscreen == fullscreen)
                    return true;
                LONG style;
                if (isfullscreen)
                    // If we are changing to fullscreen then it cant be bordered or resizable
                    style = get_style(true, false, false);
                else
                    style = get_style(false, bordered, resizable);

                if (!apply_style(hwnd, style, width, height)) return false;
                if (!apply_fullscreen(hwnd, isfullscreen, width, height)) return false;
            }
            fullscreen = isfullscreen;
            return hwnd != 0;
        }

        bool Window::setBordered(bool isbordered)
        {
            if (hwnd != 0)
            {
                if (isbordered == bordered)
                    return true;
                else if (fullscreen)
                {
                    // Will be applied next time we leave fullscreen
                    bordered = isbordered;
                    return true;
                }

                LONG style = get_style(false, isbordered, resizable);
                if (!apply_style(hwnd, style, width, height))
                    return false;
            }
            bordered = isbordered;
            return hwnd != 0;
        }

        bool Window::setResizable(bool isresizable)
        {
            if (hwnd != 0)
            {
                if (isresizable = resizable)
                    return true;

                if (fullscreen || !bordered)
                {
                    // Will change the state so the next time the state changes it
                    // will be applied
                    resizable = isresizable;
                    return true;
                }

                LONG style = get_style(false, true, isresizable);
                if (!apply_style(hwnd, style, width, height))
                    return false;
            }

            resizable = isresizable;
            return hwnd != 0;
        }

        void Window::processOsEvents()
        {
            MSG msg;
            while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                DispatchMessage(&msg);
            }
        }

        LRESULT CALLBACK Window::WindowsEventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            auto& app = Application::instanceRef;

            switch (msg)
            {
            case WM_SIZE:
            {
                app.window.width = LOWORD(lParam);
                app.window.height = HIWORD(lParam);
                return 0;
            }

            case WM_CLOSE:
            case WM_DESTROY:
                app.shutdown();
                break;

            case WM_SYSCOMMAND:
            {
                // here we block screen savers and monitor power-saving modes
                if (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER)
                    return 0;
            }break;
            }
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
}

u32 get_monitor_width()
{
    return static_cast<u32>(GetSystemMetrics(SM_CXSCREEN));
}

u32 get_monitor_height()
{
    return static_cast<u32>(GetSystemMetrics(SM_CYSCREEN));
}

LONG get_style(bool fullscreen, bool bordered, bool resizable)
{
    LONG result = WS_VISIBLE;
    if (fullscreen || !bordered)
        return result | WS_POPUP;

    // We know that we have borders to can add them to the result
    result |= WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
    if (resizable)
        result |= WS_THICKFRAME | WS_MAXIMIZEBOX;
    return result;
}

RECT get_window_style(LONG style, u32 width, u32 height)
{
    RECT wr = { 0 };
    wr.right = width;
    wr.bottom = height;

    if (!AdjustWindowRectEx(&wr, style, FALSE, STYLE_EXTENDED))
        cout << "Could not calc the window's size" << endl;
    return wr;
}

bool apply_fullscreen(HWND hwnd, bool isfullscreen, u32 clientWidth, u32 clientHeight)
{
    auto failure = [](String msg) { cout << msg << endl; return false; };

    if (isfullscreen)
    {
        DEVMODE dm;
        memset(&dm, 0, sizeof(dm));

        dm.dmSize = sizeof(DEVMODE);
        dm.dmPelsWidth = clientWidth;
        dm.dmPelsHeight = clientHeight;
        dm.dmBitsPerPel = BITS_PER_PIXEL;
        dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
            failure("Failed to enter fullscreen mode");

        if (SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW) == ERROR)
            failure("Failed to enter fullscreen mode");
    }
    else
    {
        if (ChangeDisplaySettings(0, 0) != DISP_CHANGE_SUCCESSFUL)
            failure("Failed to exit fullscreen mode");

        if (SetWindowPos(hwnd, 0, 30, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW) == ERROR)
            failure("Failed to enter fullscreen mode");
    }
    return true;
}

bool apply_style(HWND hwnd, LONG style, u32 width, u32 height)
{
    RECT wr = get_window_style(style, width, height);

    if (SetWindowLongPtr(hwnd, GWL_STYLE, style) == ERROR ||
        SetWindowPos(hwnd, 0, 0, 0, wr.right - wr.left, wr.bottom - wr.top,
            SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW) == ERROR)
    {
        cout << "Failed to apply style" << endl;
        return false;
    }
    return true;
}

bool apply_resultion(HWND hwnd, LONG style, u32 width, u32 height)
{
    RECT wr = get_window_style(style, width, height);
    if (SetWindowPos(hwnd, 0, 0, 0, wr.right - wr.left, wr.bottom - wr.top,
        SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW) == ERROR)
    {
        cout << "Failed to apply resolution" << endl;
        return false;
    }
    return true;
}

#endif
