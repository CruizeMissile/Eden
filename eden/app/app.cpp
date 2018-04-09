
#include "app.hpp"

namespace eden
{
    void app_t::create_window(const window_t::info_t& info)
    {
        window.create_window(info);
        running = true;
    }

    void app_t::update()
    {
        window.process_os_events();
        running = window.check_running_status();
    }

    void app_t::shutdown()
    {
        running = false;
    }

    void app_t::set_cursor_position(s32 x, s32 y)
    {
        window.set_cursor_position(x, y);
    }
}