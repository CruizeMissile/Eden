#pragma once

#include <pride/config/include/windows.hpp>

namespace eden::render
{
struct native_handle_t
{
    HWND window;
};

struct native_content_handle_t
{
    HWND parent;
};
} // namespace eden::render
