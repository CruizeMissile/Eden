
#include <eden/app/window.hpp>

int main()
{
    eden::window_t window;
    window.create_window();
    bool running = true;
    while (running)
    {
        window.process_os_events();
        running = window.check_running_status();
    }
}
