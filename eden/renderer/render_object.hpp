
#pragma once

namespace eden::render
{
// Everything that the render system will use will be derived from this
struct render_object_t
{
    render_object_t(const render_object_t&) = delete;
    render_object_t& operator=(const render_object_t&) = delete;

    virtual ~render_object_t() = default;

protected:
    render_object_t() = default;
};
} // namespace eden::render
