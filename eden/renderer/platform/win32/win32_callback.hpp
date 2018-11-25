#pragma once

#include <pride/config/include/windows.hpp>

namespace eden::render::internal
{
LRESULT CALLBACK win32_window_callback(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);
}
