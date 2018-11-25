
#pragma once

#include "gl_state.hpp"
#include <array>
#include <cstdint>
#include <stack>

namespace eden::render::gl
{
class gl_state_manager_t
{
public:
    gl_state_manager_t();
    ~gl_state_manager_t();

    static gl_state_manager_t* active;

    void set(gl_state_t state, bool value);
    void enable(gl_state_t state);
    void disable(gl_state_t state);

    void push_state(gl_state_t state);
    void pop_state();
    void pop_state(size_t count);

    bool is_enabled(gl_state_t state) const;

private:
    static const uint32_t num_texture_layers = 32;
    static const uint32_t num_states = (static_cast<std::uint32_t>(gl_state_t::program_point_size) + 1);

    struct gl_render_state_t
    {
        struct stack_entry_t
        {
            gl_state_t state;
            bool    enabled;
        };

        std::array<bool, num_states> values;
        std::stack<stack_entry_t>      valueStack;
    };


};
}
