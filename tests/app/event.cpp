
#include "test.hpp"
#include <eden/app/event.hpp>
#include <memory>

using namespace eden;

struct mouse_position_t : public event_t<mouse_position_t>
{
    mouse_position_t(int width, int height) : width(width), height(height) {}
    mouse_position_t(const mouse_position_t&) = default;
    int width, height = 0;
};

struct key_pressed_t : public event_t<key_pressed_t>
{
    key_pressed_t(int key) : key(key) {}
    int key;
};

TEST_CASE("Event")
{
    int width = 0;
    int height = 0;

    listener_t<mouse_position_t> mouse_listener;
    mouse_listener.callback = [&](const mouse_position_t& e)
    {
        width = e.width;
        height = e.height;
    };

    SECTION("Create event")
    {
        CHECK(width == 0);
        CHECK(height == 0);

        mouse_position_t(12, 34).raise();

        CHECK(width == 12);
        CHECK(height == 34);
    }

    SECTION("Adding to the event queue")
    {
        std::vector<int> list;

        auto compare = [](auto& one, auto& two)
        {
            return std::equal(one.begin(), one.end(), two.begin());
        };

        listener_t<key_pressed_t> listener;
        listener.callback = [&](auto& e)
        {
            list.push_back(e.key);
        };

        event_queue_t::instance().push(std::make_unique<key_pressed_t>(1));
        event_queue_t::instance().push(std::make_unique<key_pressed_t>(2));
        event_queue_t::instance().push(std::make_unique<key_pressed_t>(3));
        event_queue_t::instance().push(std::make_unique<key_pressed_t>(4));
        event_queue_t::instance().push(std::make_unique<key_pressed_t>(5));

        event_queue_t::instance().dispatch(key_pressed_t(6));

        std::vector<int> result = { 6 };
        CHECK(compare(list, result));

        std::vector<int> full_result = { 6, 1, 3, 3, 4, 5 };
        CHECK(compare(list, full_result));
    }
}
