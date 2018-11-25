
#pragma once

#include "types.hpp"
#include <vector>

namespace eden::render
{
    struct render_pass_t;

    // render target attachment type
    enum class attachment_type_t
    {
        color,
        depth,
        stencil,
        depth_stencil,
    };

    // descriptor for a render target attachment
    struct attachment_descriptor_t
    {
        attachment_descriptor_t() = default;
        attachment_descriptor_t(const attachment_descriptor_t&) = default;

        attachment_descriptor_t(attachment_type_t type) : type(type) {}

        attachment_type_t type = attachment_type_t::color;
    };

    // descriptor for a render target
    struct render_target_descriptor_t
    {
        const render_pass_t* render_pass = nullptr;
        extent2_t resolution;
        std::vector<attachment_descriptor_t> attachments;
    };
}
