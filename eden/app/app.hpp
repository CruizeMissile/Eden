
#pragma once

#include "window.hpp"
#include "input.hpp"
#include <pride/types.hpp>
#include <pride/utility/singleton.hpp>

namespace eden
{
    class app_t : public pride::singleton_t<app_t>
    {
        friend class input_t;

    public:
        app_t() = default;
        ~app_t() = default;

        void create_window(const window_t::info_t& info = window_t::info_t::default);
        void update();
        void shutdown();

        bool running = false;
        window_t window;

    private:
        void get_cursor_position();
        void set_cursor_position(s32 x, s32 y);
    };
}
