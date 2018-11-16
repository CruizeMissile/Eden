
#include <eden/ecs.hpp>
#include <iostream>
#include <string>
#include <cassert>

namespace ours
{
struct health_t : eden::ecs::property<uint32_t>{};
struct mana_t : eden::ecs::property<uint32_t>{};
struct name_t : eden::ecs::property<std::string>{};
struct caster_t : public eden::ecs::archetype<health_t, mana_t, name_t> {};
}

template<typename Type>
eden::ecs::dynamic_bitset<32> build_mask()
{
    auto mask = eden::ecs::dynamic_bitset(1 << eden::ecs::get_component_id<Type>() );
    return mask;
}

template<typename One, typename Two, typename... Types>
eden::ecs::dynamic_bitset<32> build_mask()
{
    auto mask = build_mask<One>() | build_mask<Two, Types...>();
    return mask;
}

int main()
{
    using namespace eden::ecs;
    size_t value = 3147483647;


    //std::bitset<16> bitset(value);
    //std::cout << bitset.to_string() << '\n';
    //dynamic_bitset<32> mask(value);
    //std::cout << mask.to_string() << '\n';

    return 0;
}
