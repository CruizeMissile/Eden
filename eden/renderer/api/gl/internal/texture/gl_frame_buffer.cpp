
#include "gl_frame_buffer.hpp"

namespace eden::render::gl
{
~gl_frame_buffer_t::gl_frame_buffer_t()
{
    destroy();
}

gl_frame_buffer_t::gl_frame_buffer_t(gl_frame_buffer_t&& rhs)
: id_(rhs.id_)
{
    rhs.id_ = 0;
}

gl_frame_buffer_t& gl_frame_buffer_t::operator=(gl_frame_buffer_t&& rhs)
{
    if (id_ != rhs.id_)
    {
        destroy();
        id_ = rhs.id_;
        rhs.id_ = 0;
    }

    return *this;
}

void gl_frame_buffer_t::generate()
{
    destroy();
    glGenFramebuffers(1, &id_);
}

void gl_frame_buffer_t::destroy()
{
    if (id_ != 0)
    {
        glDeleteFrameBuffers(1, &id_);
        id_ = 0;
    }
}

void gl_frame_buffer_t::bind(const gl_framebuffer_target_t target = gl_framebuffer_target_t::framebuffer) const
{

}

void gl_frame_buffer_t::unbind(const gl_framebuffer_target_t target = gl_framebuffer_target_t::framebuffer) const
{

}

GLuint gl_frame_buffer_t::id()
{
    return id_;
}

bool gl_frame_buffer_t::valid()
{
    return (id_ != 0);
}

operator gl_frame_buffer_t::bool()
{
    return valid();
}


}
