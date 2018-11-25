
#pragma once

#include "../../opengl.hpp"

namespace eden::render::gl
{
enum class gl_state_t
{
    blend = 0,
    color_logic_op,
    cull_face,
    debug_output,
    debug_output_synchronous,
    depth_clamp,
    depth_test,
    dither,
    framebuffer_srgb,
    line_smooth,
    multisample,
    polygon_offset_fill,
    polygon_offset_line,
    polygon_offset_point,
    polygon_smooth,
    primitive_restart,
    primitive_restart_fixed_index,
    rasterizer_discard,
    sample_alpha_to_coverage,
    sample_alpha_to_one,
    sample_coverage,
    sample_shading,
    sample_mask,
    scissor_test,
    stencil_test,
    texture_cube_map_seamless,
    program_point_size,
};

enum class gl_buffer_target_t
{
    array_buffer = 0,
    atomic_counter_buffer,
    copy_read_buffer,
    copy_write_buffer,
    dispatch_indirect_buffer,
    draw_indirect_buffer,
    element_array_buffer,
    pixel_pack_buffer,
    pixel_unpack_buffer,
    query_buffer,
    shader_storage_buffer,
    texture_buffer,
    transform_feedback_buffer,
    uniform_buffer,
};

enum class gl_framebuffer_target_t
{
    framebuffer = 0,
    draw_framebuffer,
    read_framebuffer,
};

}
