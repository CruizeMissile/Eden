
#pragma once

#include "../render_state/gl_state.hpp"

namespace eden::render::gl
{
class gl_frame_buffer_t
{
public:
    gl_frame_buffer_t() = default;
    ~gl_frame_buffer_t();

    gl_frame_buffer_t(const gl_frame_buffer_t&) = delete;
    gl_frame_buffer_t& operator=(const gl_frame_buffer_t&) = delete;

    gl_frame_buffer_t(gl_frame_buffer_t&& rhs);
    gl_frame_buffer_t& operator=(gl_frame_buffer_t&& rhs);

    void generate();
    void destroy();

    void bind(const gl_framebuffer_target_t target = gl_framebuffer_target_t::framebuffer) const;
    void unbind(const gl_framebuffer_target_t target = gl_framebuffer_target_t::framebuffer) const;

    GLuint id();
    bool valid();
    operator bool();

private:
    GLuint id_;
};
}
