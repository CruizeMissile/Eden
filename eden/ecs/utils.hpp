
#pragma once

#include "defines.hpp"
#include "mask.hpp"

namespace eden::ecs
{
struct entity_t;
}

namespace eden::ecs::internal
{
template<typename Type>
mask_t component_mask()
{
    if constexpr (std::is_same_v<Type, entity_t>)
        return mask_t();
    return mask_t((1ull << get_component_id<Type>()));
}

template<typename Type1, typename Type2, typename... Types>
mask_t component_mask()
{
    mask_t mask = component_mask<Type1>() | component_mask<Type2, Types...>();
    return mask;
}
} // namespace eden::ecs::internal
