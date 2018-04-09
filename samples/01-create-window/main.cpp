
#include <eden/app/app.hpp>
#include <iostream>

struct some_container_t
{
    eden::listener_t<eden::events::mouse_movement_t> on_mouse_move;
    eden::listener_t<eden::events::mouse_button_down_t> on_mouse_down;
    eden::listener_t<eden::events::mouse_button_up_t> on_mouse_up;
    eden::listener_t<eden::events::key_down_t> on_key_down;
    eden::listener_t<eden::events::key_up_t> on_key_up;
    eden::listener_t<eden::events::window_entered_t> on_window_enter;
    eden::listener_t<eden::events::window_exited_t> on_window_exit;
    eden::listener_t<eden::events::drag_and_drop_t> on_drag_and_drop;

    some_container_t()
    {
        on_mouse_move.callback = [](auto& e) { std::cout << e.x << " : " << e.y << '\n'; };
        on_mouse_down.callback = [](auto& e) { std::cout << static_cast<u32>(e.button) << '\n'; };
        on_mouse_up.callback = [](auto& e) { std::cout << static_cast<u32>(e.button) << '\n'; };
        on_key_down.callback = [](auto& e) { if (e.key == eden::key_t::escape) eden::app_t::instance().running = false; std::cout << static_cast<u32>(e.key) << '\n'; };
        on_key_up.callback = [](auto& e) { std::cout << static_cast<u32>(e.key) << '\n'; };
        on_window_enter.callback = [](auto& e) { std::cout << "Entered" << '\n'; };
        on_window_exit.callback = [](auto& e) { std::cout << "Exit" << '\n'; };
        on_drag_and_drop.callback = [](auto& e) { std::cout << e.file << '\n'; };
    }
};

int main()
{
    using namespace eden;
    app_t::instance().create_window();

    some_container_t some_container;
    while (app_t::instance().running)
    {
        app_t::instance().update();
        event_queue_t::instance().dispatch();
    }

    app_t::instance().shutdown();
    return 0;
}
