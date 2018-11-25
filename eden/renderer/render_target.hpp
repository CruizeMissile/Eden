
#pragma once

#include "render_object.hpp"
#include "render_pass.hpp"
#include "render_target_flags.hpp"
#include "types.hpp"

namespace eden::render
{
class render_target_t : public render_object_t
{
public:
    virtual bool is_render_context() const;
    virtual extent2_t get_resolution() const = 0;
    virtual uint32_t get_num_color_attachments() const = 0;
    virtual bool has_depth_attachment() const = 0;
    virtual bool has_stencil_attachment() const = 0;
    virtual const render_pass_t* get_render_pass() const = 0;
};
} // namespace eden::render
