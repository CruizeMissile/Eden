
#pragma once

#include "defines.hpp"
#include "mask.hpp"
#include <tuple>

namespace eden::ecs
{
struct entity_t;

namespace internal
{
    template<typename Type>
    struct function_traits : public function_traits<decltype(&Type::operator())>
    {
    };

    template<typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType (ClassType::*)(Args...) const>
    {
        enum
        {
            arg_count = sizeof...(Args)
        };

        using return_type = ReturnType;

        template<size_t i>
        struct arg_t
        {
            using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
        };

        template<size_t N>
        using arg = typename arg_t<N>::type;

        template<size_t N>
        struct arg_remove_ref_t
        {
            using type = typename std::remove_reference<arg<N>>::type;
        };

        template<size_t N>
        using arg_remove_ref = typename arg_remove_ref_t<N>::type;
        using args = std::tuple<Args...>;
    };

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
} // namespace internal
} // namespace eden::ecs
