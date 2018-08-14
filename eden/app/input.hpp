
#pragma once

#include "event.hpp"
#include <pride/types.hpp>
#include <pride/utility/singleton.hpp>

#include <string>

namespace eden
{
enum class key_t
{
    unknown = -1,
    space = 32,
    apostrophe = 39,
    comma = 44,
    minus,
    period,
    slash,
    key0 = 48,
    key1,
    key2,
    key3,
    key4,
    key5,
    key6,
    key7,
    key8,
    key9,
    a = 65,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    left_bracket,
    backslash,
    right_bracket,
    grave = 96,
    semicolen = 59,
    equals = 61,
    escape = 256,
    enter,
    tab,
    backspace,
    insert,
    delete_key,
    right,
    left,
    down,
    up,
    pageup,
    pagedown,
    home,
    end,
    capsLock = 280,
    scrollLock,
    num_lock,
    print_screen,
    pause,
    f1 = 290,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,
    f13,
    f14,
    f15,
    f16,
    f17,
    f18,
    f19,
    f20,
    f21,
    f22,
    f23,
    f24,
    f25,
    key_pad0,
    key_pad1,
    key_pad2,
    key_pad3,
    key_pad4,
    key_pad5,
    key_pad6,
    key_pad7,
    key_pad8,
    key_pad9,
    key_pad_decimal,
    key_paddivide,
    key_pad_multiply,
    key_pad_subtract,
    key_pad_Add,
    key_pad_enter,
    key_pad_equal,
    left_shift = 340,
    left_contorl,
    left_alt,
    left_super,
    right_shift,
    right_control,
    right_alt,
    right_super,
    menu,
    total_ammount
};

enum class mouse_button_t
{
    Unknown = -1,
    left = 0,
    right,
    middle,
    button1 = 0,
    button2,
    button3,
    button4,
    button5,
    button6,
    button7,
    button8,
    total_ammount
};

class input_t : public pride::singleton_t<input_t>
{
    friend class app_t;

public:
    bool is_down(const key_t key) const noexcept;
    bool is_up(const key_t key) const noexcept;

    bool is_down(const mouse_button_t button) const noexcept;
    bool is_up(const mouse_button_t button) const noexcept;

    void set_key_state(const key_t key, bool state) noexcept;
    void set_mouse_btn_state(const mouse_button_t button, bool state) noexcept;

    void get_cursor_position() const noexcept;
    void set_cursor_position(s32 x, s32 y) noexcept;
    void update_cursor_position(s32 x, s32 y) noexcept;

private:
    void update();

    bool keys[static_cast<u32>(key_t::total_ammount)] = { false };
    u32 xpos, ypos;
};

namespace events
{
    struct key_down_t : public event_t<key_down_t>
    {
        key_down_t(const key_t key)
            : key(key)
        {}
        key_t key;
    };

    struct key_up_t : public event_t<key_up_t>
    {
        key_up_t(const key_t key)
            : key(key)
        {}
        key_t key;
    };

    struct mouse_button_down_t : public event_t<mouse_button_down_t>
    {
        mouse_button_down_t(const mouse_button_t button)
            : button(button)
        {}
        mouse_button_t button;
    };

    struct mouse_button_up_t : public event_t<mouse_button_up_t>
    {
        mouse_button_up_t(const mouse_button_t button)
            : button(button)
        {}
        mouse_button_t button;
    };

    struct mouse_movement_t : public event_t<mouse_movement_t>
    {
        mouse_movement_t(const u32 x, const u32 y)
            : x(x)
            , y(y)
        {}
        u32 x, y;
    };

    struct drag_and_drop_t : public event_t<drag_and_drop_t>
    {
        drag_and_drop_t(const char* file)
            : file(file)
        {}
        drag_and_drop_t(const std::string& file_path)
            : file(file_path)
        {}
        std::string file;
    };
} // namespace events
} // namespace eden
