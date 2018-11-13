
#include <eden/ecs.hpp>
#include <iostream>
#include <string>
#include <cassert>

struct health_t : eden::ecs::property<uint32_t>{};
struct mana_t : eden::ecs::property<uint32_t>{};
struct name_t : eden::ecs::property<std::string>{};

struct caster_t : public eden::ecs::archetype<health_t, mana_t, name_t> {};

int main()
{
    using namespace eden::ecs;

    director_t d;
    entity_t ent = d.create<caster_t>();

    return 0;
}
