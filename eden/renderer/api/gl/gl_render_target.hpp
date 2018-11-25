
#pragma once

#include "../../render_target.hpp"

namespace eden::render
{
    class gl_render_target_t final : public render_target_t
    {
    public:
        gl_render_target_t(const render_target_descriptor_t& desc);

        extent2_t get_resolution() const override;

        extent2_t get_resolution() const override;
        uint32_t get_num_color_attachments() const override;
        bool has_depth_attachment() const override;
        bool has_stencil_attachment() const override;
        const render_pass_t* get_render_pass() const override;

    };
}
