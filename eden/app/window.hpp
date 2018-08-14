
#pragma once

#include "event.hpp"

#include <pride/types.hpp>
#include <string>

namespace eden
{
class window_t;
class app_t;

class window_t
{
    friend class app_t;

public:
    struct info_t
    {
        static const info_t default_config;
        std::string title;
        u32 width;
        u32 height;
        bool fullscreen;
        bool bordered;
        bool resizable;
    };

    window_t() = default;
    ~window_t();

    void create_window(const info_t& info = info_t::default_config);

    bool check_running_status();

    u32 get_width() const noexcept;
    u32 get_height() const noexcept;

    bool is_fullscreen() const noexcept;
    bool is_bordered() const noexcept;
    bool is_resizeable() const noexcept;

    void set_fullscreen(const bool fullscreen) noexcept;
    void set_bordered(const bool bordered) noexcept;
    void set_resizable(const bool resizable) noexcept;

    void process_os_events();

protected:
    void set_cursor_position(u32 x, u32 y);
    void get_cursor_position();

private:
    std::string title;
    u32 width;
    u32 height;
    s32 xpos;
    s32 ypos;
    bool fullscreen = false;
    bool bordered = true;
    bool resizeable = true;
};

namespace events
{
    struct window_entered_t : public event_t<window_entered_t>
    {};
    struct window_exited_t : public event_t<window_exited_t>
    {};
} // namespace events
} // namespace eden
