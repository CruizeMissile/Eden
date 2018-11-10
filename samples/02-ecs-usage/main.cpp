
#include <eden/ecs.hpp>
#include <iostream>
#include <string>
#include <cassert>

struct health_t
{
    size_t value = 10;
};

struct mana_t
{
    size_t value = 100;
};

struct name_t
{
    std::string value = "something";
};

struct bob_t : public eden::ecs::archetype<health_t, mana_t, name_t>
{

};

struct rob_t : public eden::ecs::archetype<health_t, name_t>
{

};

int main()
{
    using namespace eden::ecs;

    director_t d;
    entity_t bob = d.create<bob_t>();
    entity_t rob = d.create<rob_t>();

    return 0;
}
