
#pragma once

#include "render_context_flags.hpp"
#include <cstdint>

namespace eden::render
{
struct surface_t
{
    surface_t() = default;
    surface_t(const surface_t&) = delete;
    surface_t& operator=(const surface_t&) = delete;
    virtual ~surface_t() = default;

    virtual void get_native_handle(void* handle) const = 0;
    virtual extent2_t get_content_size() const = 0;
    virtual bool adapt_for_video_mode(video_mode_descriptor_t& desc) = 0;
    virtual void reset_pixel_format() = 0;
};
} // namespace eden::render
