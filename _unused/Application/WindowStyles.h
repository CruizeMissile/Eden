#pragma once
#include "../Core/TFlags.h"


namespace edn
{
    enum class WindowStyle : u32
    {
        FULLSCREEN = 1 << 0,
        BORDERED   = 1 << 1,
        BORDERLESS = 1 << 3,
        FIXED      = 1 << 2,
        RESIZE     = 1 << 4,
    };
    using WindowStyleFlag = TFlags<WindowStyle>;
}
