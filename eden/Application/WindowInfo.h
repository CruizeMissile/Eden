#pragma once
#include "Core/Types.h"

namespace edn
{
    struct WindowInfo
    {
        // A default version of windowinfo
        static const WindowInfo Default;

        u32 width;
        u32 height;
        String title;
        bool fullscreen;
        bool bordered;
        bool resizable;
    };
}
