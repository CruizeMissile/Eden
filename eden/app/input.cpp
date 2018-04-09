
#include "input.hpp"
#include "app.hpp"

namespace eden
{
    bool input_t::is_down(const key_t key) const noexcept
    {
        return keys[static_cast<u32>(key)];
    }

    bool input_t::is_up(const key_t key) const noexcept
    {
        return !is_down(key);
    }

    bool input_t::is_down(const mouse_button_t button) const noexcept
    {
        return keys[static_cast<u32>(button)];
    }

    bool input_t::is_up(const mouse_button_t button) const noexcept
    {
        return !is_down(button);
    }

    void input_t::set_key_state(const key_t key, bool state) noexcept
    {
         keys[static_cast<u32>(key)] = state;
    }

    void input_t::set_mouse_btn_state(const mouse_button_t button, bool state) noexcept
    {
         keys[static_cast<u32>(button)] = state;
    }

    void input_t::get_cursor_position() const noexcept
    {

    }

    void input_t::set_cursor_position(s32 x, s32 y) noexcept
    {
        app_t::instance().set_cursor_position(x, y);
    }

    void input_t::update_cursor_position(s32 x, s32 y) noexcept
    {
        xpos = x;
        ypos = y;
    }

    void input_t::update()
    {

    }
}
