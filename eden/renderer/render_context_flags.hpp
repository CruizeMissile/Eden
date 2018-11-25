
#pragma once

#include "types.hpp"
#include <cstdint>

namespace eden::render
{
struct vsync_descriptor_t
{
    bool enabled = false;
    uint32_t refreshRate = 60;
    uint32_t interval = 1;
};

struct video_mode_descriptor_t
{
    extent2_t resolution;
    uint32_t color_bits = 32;
    uint32_t depth_bits = 24;
    uint32_t stencil_bits = 8;
    bool fullscreen = false;
    uint32_t swapchain_size = 2;
};

struct render_context_descriptor_t
{
    vsync_descriptor_t vsync;
    video_mode_descriptor_t video_mode;
};
} // namespace eden::render
