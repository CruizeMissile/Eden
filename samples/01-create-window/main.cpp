
#include <eden/app/app.hpp>

int main()
{
    using namespace eden;
    app_t::instance().create_window();

    while (app_t::instance().running)
    {
        app_t::instance().update();
        event_queue_t::instance().dispatch();
    }
    
    app_t::instance().shutdown();
    return 0;
}
