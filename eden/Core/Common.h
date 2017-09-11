#ifndef H_CORE_COMMON_H
#define H_CORE_COMMON_H

#include "Types.h"

namespace edn
{
    //
    // NonCopyable
    //
    class NonCopyable
    {
    public:
        NonCopyable() { }
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    struct IRect
    {
        u32 width;
        u32 height;
    };

    struct IPoint
    {
        u32 x;
        u32 y;
    };

}

#endif
