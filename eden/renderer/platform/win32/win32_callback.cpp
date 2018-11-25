
#include "win32_callback.hpp"
#include "win32_keymap.hpp"
#include "win32_window.hpp"
#include <iostream>
#include <pride/config/include/windows.hpp>
#include <windowsx.h>

namespace eden::render::internal
{
static win32_window_t* get_window_from_user_data(HWND wnd)
{
    return reinterpret_cast<win32_window_t*>(GetWindowLongPtr(wnd, GWLP_USERDATA));
}

static void post_key_event(window_t& window, input::key_t keycode, bool is_down)
{
    if (is_down)
        window.post_key_down(keycode);
    else
        window.post_key_up(keycode);
}

static void post_key_event(HWND wnd, WPARAM wparam, LPARAM lparam, bool is_down)
{
    if (auto window = get_window_from_user_data(wnd))
    {
        auto sys_keycode = static_cast<uint8_t>(wparam);
        auto oem_keycode = static_cast<uint32_t>(lparam & (0xff << 16)) >> 16;
        auto is_extended_key = ((lparam & (1 << 24)) != 0);

        auto keycode = internal::map_key(sys_keycode);
        std::cout << static_cast<uint16_t>(keycode) << "\n";
        post_key_event(*window, keycode, is_down);
    }
}

static int mouse_capture_couter = 0;

static void release_mouse_capture()
{
    if (mouse_capture_couter > 0)
    {
        mouse_capture_couter = 0;
        ReleaseCapture();
    }
}

static void capture_mouse_button(HWND wnd, input::key_t keycode, bool double_click = false)
{
    if (auto window = get_window_from_user_data(wnd))
    {
        window->post_key_down(keycode);

        if (double_click)
            window->post_double_click(keycode);

        if (++mouse_capture_couter == 1)
            SetCapture(wnd);
    }
}

static void release_mouse_button(HWND wnd, input::key_t keycode)
{
    if (auto window = get_window_from_user_data(wnd))
    {
        window->post_key_up(keycode);

        if (--mouse_capture_couter == 0)
            ReleaseCapture();

        if (mouse_capture_couter < 0)
            mouse_capture_couter = 0;
    }
}

static void post_local_mouse_motion(HWND wnd, LPARAM lparam)
{
    if (auto window = get_window_from_user_data(wnd))
    {
        int x = GET_X_LPARAM(lparam);
        int y = GET_Y_LPARAM(lparam);
        window->post_local_motion({ x, y });
    }
}

static void post_global_mouse_motion(HWND wnd, LPARAM lparam)
{
    if (auto window = get_window_from_user_data(wnd))
    {
        RAWINPUT raw;
        UINT raw_size = sizeof(raw);

        GetRawInputData(
            reinterpret_cast<HRAWINPUT>(lparam),
            RID_INPUT,
            &raw,
            &raw_size,
            sizeof(RAWINPUTHEADER));

        if (raw.header.dwType == RIM_TYPEMOUSE)
        {
            const auto& mouse = raw.data.mouse;
            if (mouse.usFlags == MOUSE_MOVE_RELATIVE)
            {
                int dx = mouse.lLastX;
                int dy = mouse.lLastY;
                window->post_global_motion({ dx, dy });
            }
        }
    }
}

LRESULT CALLBACK win32_window_callback(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        RAWINPUTDEVICE device;
        device.dwFlags = RIDEV_INPUTSINK;
        device.hwndTarget = wnd;
        device.usUsage = static_cast<USHORT>(0x02);
        device.usUsagePage = static_cast<USHORT>(0x01);
        RegisterRawInputDevices(&device, 1, sizeof(device));
    }
    break;

    case WM_SIZE:
    {
        if (auto window = get_window_from_user_data(wnd))
        {
            WORD width = LOWORD(lparam);
            WORD height = HIWORD(lparam);
            window->post_resize({ static_cast<uint32_t>(width), static_cast<uint32_t>(height) });
        }
    }
    break;

    case WM_CLOSE:
    {
        if (auto window = get_window_from_user_data(wnd))
            window->post_quit();
    }
    break;

    case WM_SYSCOMMAND:
    {
    }
    break;

    case WM_SETFOCUS:
    {
        if (auto window = get_window_from_user_data(wnd))
            window->post_get_focus();
    }
    break;

    case WM_KILLFOCUS:
    {
        if (auto window = get_window_from_user_data(wnd))
            window->post_lose_forcus();
    }
        return 0;

    case WM_KEYDOWN:
    {
        post_key_event(wnd, wparam, lparam, true);
    }
        return 0;

    case WM_KEYUP:
    {
        post_key_event(wnd, wparam, lparam, false);
    }
        return 0;

    case WM_SYSKEYDOWN:
    {
        post_key_event(wnd, wparam, lparam, true);
    }
        return 0;

    case WM_SYSKEYUP:
    {
        post_key_event(wnd, wparam, lparam, false);
    }
        return 0;

    case WM_CHAR:
    {
        if (auto window = get_window_from_user_data(wnd))
            window->post_char(static_cast<char>(wparam));
    }
        return 0;

    case WM_LBUTTONDOWN:
    {
        capture_mouse_button(wnd, input::key_t::left_button);
    }
        return 0;

    case WM_LBUTTONUP:
    {
        release_mouse_button(wnd, input::key_t::left_button);
    }
        return 0;

    case WM_LBUTTONDBLCLK:
    {
        capture_mouse_button(wnd, input::key_t::left_button, true);
    }
        return 0;

    case WM_RBUTTONDOWN:
    {
        capture_mouse_button(wnd, input::key_t::right_button);
    }
        return 0;

    case WM_RBUTTONUP:
    {
        release_mouse_button(wnd, input::key_t::right_button);
    }
        return 0;

    case WM_RBUTTONDBLCLK:
    {
        capture_mouse_button(wnd, input::key_t::right_button, true);
    }
        return 0;

    case WM_MBUTTONDOWN:
    {
        capture_mouse_button(wnd, input::key_t::middle_button);
    }
        return 0;

    case WM_MBUTTONUP:
    {
        release_mouse_button(wnd, input::key_t::middle_button);
    }
        return 0;

    case WM_MBUTTONDBLCLK:
    {
        capture_mouse_button(wnd, input::key_t::middle_button, true);
    }
        return 0;

    case WM_MOUSEWHEEL:
    {
        if (auto window = get_window_from_user_data(wnd))
            window->post_wheel_motion(GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA);
    }
        return 0;

    case WM_MOUSEMOVE:
    {
        post_local_mouse_motion(wnd, lparam);
    }
        return 0;

    case WM_INPUT:
    {
        post_global_mouse_motion(wnd, lparam);
    }
        return 0;

    case WM_ERASEBKGND:
    {
        if (auto window = get_window_from_user_data(wnd))
        {
            if (window->behavior().disable_clear_on_resize)
                return 0;
        }
    }
    break;

    case WM_ENTERSIZEMOVE:
    {
        if (auto window = get_window_from_user_data(wnd))
        {
            auto timer_id = window->behavior().move_and_release_timer_id;
            if (timer_id != 0u)
                SetTimer(wnd, timer_id, USER_TIMER_MINIMUM, nullptr);
        }
    }
    break;

    case WM_EXITSIZEMOVE:
    {
        if (auto window = get_window_from_user_data(wnd))
        {
            auto timer_id = window->behavior().move_and_release_timer_id;
            if (timer_id != 0u)
                KillTimer(wnd, timer_id);
        }
    }
    break;

    case WM_TIMER:
    {
        std::cout << static_cast<uint32_t>(wparam) << '\n';
    }
    break;
    }

    return DefWindowProc(wnd, msg, wparam, lparam);
}
} // namespace eden::render::internal
