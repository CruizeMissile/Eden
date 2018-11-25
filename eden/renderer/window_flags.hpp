
#pragma once

#include "types.hpp"
#include <cstdint>
#include <string>

namespace eden::render
{
struct window_behavior_t
{
    bool disable_clear_on_resize = false;
    uint32_t move_and_release_timer_id = 0u;
};

struct window_descriptor_t
{
    std::string title;
    offset2_t position;
    extent2_t size;
    bool visible = false;
    bool borderless = false;
    bool resizable = false;
    bool centered = false;
    const void* context = nullptr;
};
} // namespace eden::render
