
#pragma once

#include <cstdint>

namespace eden::render
{
struct extent2_t
{
    extent2_t() = default;
    extent2_t(const extent2_t&) = default;
    extent2_t(uint32_t width, uint32_t height)
        : width(width)
        , height(height)
    {}

    uint32_t width = 0;
    uint32_t height = 0;
};

struct offset2_t
{
    offset2_t() = default;
    offset2_t(const offset2_t&) = default;
    offset2_t(int32_t x, int32_t y)
        : x(x)
        , y(y)
    {}

    int32_t x = 0;
    int32_t y = 0;
};
} // namespace eden::render
