
#include "test.hpp"
#include <eden/ecs.hpp>
#include <string>

using namespace eden::ecs;

struct health_t : property<uint32_t> {};
struct mana_t : property<uint32_t> {};
struct name_t : property<std::string> {};

TEST_CASE("Ecs system")
{
    director_t director;

    SECTION("Static Id counters")
    {
        auto c_zero = get_component_id<char>();
        auto c_one = get_component_id<int>();
        auto c_two = get_component_id<float>();
        auto c_three = get_component_id<double>();

        auto s_zero = get_system_id<double>();
        auto s_one = get_system_id<float>();
        auto s_two = get_system_id<int>();
        auto s_three = get_system_id<char>();

        CHECK(c_zero == 0);
        CHECK(c_one == 1);
        CHECK(c_two == 2);
        CHECK(c_three == 3);

        CHECK(s_zero == 0);
        CHECK(s_one == 1);
        CHECK(s_two == 2);
        CHECK(s_three == 3);
    }

    SECTION("Create an entity")
    {
        auto ent = director.create();

        CHECK(director.count() == 1);
        CHECK(ent.is_valid());

        ent.destroy();
        CHECK(director.count() == 0);
        CHECK(!ent.is_valid());

        auto ents = director.create(100);
        CHECK(director.count() == 100);

        bool toggle = true;
        for (auto e : ents)
        {
            if (toggle)
                e.destroy();
            toggle = !toggle;
        }

        CHECK(director.count() == 50);
    }

    SECTION("Add and remove entity")
    {
        auto ent = director.create();

        auto health = ent.add<health_t>();
        CHECK(ent.has<health_t>());
        CHECK(health == 0);

        health = ent.set<health_t>(10u);
        CHECK(health == 10);

        ent.remove<health_t>();
        CHECK(!ent.has<health_t>());

        ent.add<health_t>();
    }
}
