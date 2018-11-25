
#include <eden/renderer.hpp>
#include <iostream>

int main()
{
    using namespace eden;

    render::window_descriptor_t win_desc;
    win_desc.size = { 1280, 720 };
    win_desc.centered = true;
    win_desc.resizable = true;

    auto window = render::window_t::create(win_desc);
    window->show();

    while (window->process_events())
    {
    }

    window->show(false);
    return 0;
}
