
#include <type_traits>

namespace eden::ecs::internal
{
template<typename Type>
mask_t component_mask()
{
    if constexpr (std::is_same_v<Type, component>)
        return mask_t();
    return mask_t((1ul << get_component_id<Component>()));
}

template<typename Type1, typename Type2, typename... Types>
mask_t component_mask()
{
    return component_mask<Type1>() | component_mask<Type2, Types...>();
}
} // namespace eden::ecs::internal
