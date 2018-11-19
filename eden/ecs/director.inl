
#include "entity.hpp"
#include "iterator.hpp"
#include "store.hpp"
#include "utils.hpp"
#include "view.hpp"
#include <cassert>
#include <type_traits>
#include <utility>

namespace eden::ecs
{
namespace internal
{
    template<size_t N, typename Lambda, typename... Args>
    struct with_t<N, Lambda, Args...> : with_t<N - 1, Lambda,
                                            typename internal::function_traits<Lambda>::template arg_remove_ref<N - 1>, Args...>
    {
    };

    template<typename Lambda, typename... Args>
    struct with_t<0, Lambda, Args...>
    {
        static void for_each(director_t& director, Lambda lambda)
        {
            using function = typename internal::function_traits<Lambda>;
            static_assert(function::arg_count > 0, "Lambda or function must have at least 1 argument.");

            auto view = director.with<Args...>();
            auto it = view.begin();
            auto end = view.end();
            for (; it != end; ++it)
                lambda(get_arg<Args>(director, it.index())...);
        }

        template<typename Type>
        static auto get_arg(director_t& director, index_t index) ->
            typename std::enable_if<!std::is_same<Type, entity_t>::value, Type&>::type
        {
            return director.get_component_fast<Type>(index);
        }

        template<typename Type>
        static auto get_arg(director_t& director, index_t index) ->
            typename std::enable_if<std::is_same<Type, entity_t>::value, entity_t>::type
        {
            return director.get_entity(index);
        }
    };

    template<typename Lambda>
    using with_ = with_t<internal::function_traits<Lambda>::arg_count, Lambda>;
} // namespace internal

template<typename Lambda>
void director_t::create(const size_t n, Lambda lambda)
{
    using arch_type = typename internal::function_traits<Lambda>::template arg_remove_ref<0>;
    for (entity_t& ent : create(n))
    {
        lambda(*reinterpret_cast<arch_type*>(&ent));
    }
}

template<typename Archetype, typename... Args>
auto director_t::create(Args&&... args) ->
    typename std::enable_if_t<std::is_base_of_v<internal::base_archetype_t, Archetype> || std::is_base_of_v<entity_t, Archetype>, Archetype&>
{
    auto mask = Archetype::static_mask();
    entity_t ent = create();

    // If the Archetype is constructable with args the call the constructor
    if constexpr (std::is_constructible<Archetype, Args...>::value)
    {
        Archetype* arch = new (&ent) Archetype(std::forward<Args>(args)...);
        assert(ent.has(mask));
        return *arch;
    }
    else
    {
        // If the Archetype is not constructable with Args then try calling the init
        // function and then cast to the passed in Archetype type
        using arch_type = typename Archetype::this_type;
        arch_type* arch = new (&ent) arch_type();
        arch->init(std::forward<Args>(args)...);
        return *reinterpret_cast<Archetype*>(arch);
    }
}

template<typename... Components, typename... Args>
auto director_t::create_with(Args&&... args) ->
    typename std::conditional<(sizeof...(Components) > 0), archetype<Components...>, archetype<Args...>>::type
{
    using return_type = typename std::conditional<(sizeof...(Components) > 0), archetype<Components...>, archetype<Args...>>::type;
    entity_t e = create();
    return_type* arch = new (&e) return_type();
    arch->init(std::forward<Args>(args)...);
    return *arch;
}

template<typename... Components>
archetype<Components...> director_t::create_with()
{
    using return_type = archetype<Components...>;
    entity_t e = create();
    return_type* arch = new (&e) return_type();
    arch->init();
    return *arch;
}

template<typename... Components>
view<archetype<Components...>> director_t::with()
{
    mask_t mask = internal::component_mask<Components...>();
    return view<archetype<Components...>>(this, mask);
}

template<typename Lambda>
void director_t::with(Lambda lambda)
{
    internal::with_<Lambda>::for_each(*this, lambda);
}

template<typename Archetype>
view<Archetype> director_t::fetch_every()
{
    return view<Archetype>(this, Archetype::static_mask());
}

template<typename Lambda>
void director_t::fetch_every(Lambda lambda)
{
    using function = internal::function_traits<Lambda>;
    using entity_interface_t = typename function::template arg_remove_ref<0>;
    static_assert(function::arg_count == 1, "Lambda or function must only have one argument");

    for (entity_interface_t interface : fetch_every<entity_interface_t>())
        lambda(interface);
}

template<typename Component, typename... Args>
store<Component>& director_t::create_store(Args&&... args)
{
    store<Component>* ptr = new store<Component>(std::forward<director_t&>(*this), std::forward<Args>(args)...);
    stores_[get_component_id<Component>()] = ptr;
    return *ptr;
}

template<typename Component>
store<Component>& director_t::get_store_fast()
{
    return *reinterpret_cast<store<Component>*>(stores_[get_component_id<Component>()]);
}

template<typename Component>
store<const Component>& director_t::get_store_fast() const
{
    return *reinterpret_cast<store<Component>*>(stores_[get_component_id<Component>()]);
}

template<typename Component>
store<Component>& director_t::get_store()
{
    auto index = get_component_id<Component>();
    if (stores_.size() <= index)
    {
        stores_.resize(index + 1, nullptr);
        return create_store<Component>();
    }
    else if (stores_[index] == nullptr)
    {
        return create_store<Component>();
    }
    return *reinterpret_cast<store<Component>*>(stores_[index]);
}

template<typename Component>
const store<Component>& director_t::get_store() const
{
    auto index = get_component_id<Component>();
    return *reinterpret_cast<store<Component>*>(stores_[index]);
}

template<typename Component>
Component& director_t::get_component(entity_t& entity)
{
    return get_store<Component>().get(entity.id_.index);
}

template<typename Component>
const Component& director_t::get_component(const entity_t& entity) const
{
    return get_store<Component>().get(entity.id_.index);
}

template<typename Component>
Component& director_t::get_component_fast(index_t index)
{
    return get_store_fast<Component>().get(index);
}

template<typename Component>
const Component& director_t::get_component_fast(index_t index) const
{
    return get_store_fast<Component>().get(index);
}

template<typename Component>
Component& director_t::get_component_fast(entity_t& entity)
{
    return get_store_fast<Component>().get(entity.id_.index);
}

template<typename Component>
const Component& director_t::get_component_fast(const entity_t& entity) const
{
    return get_store_fast<Component>().get(entity.id_.index);
}

template<typename Component, typename... Args>
Component& director_t::create_component(entity_t& entity, Args&&... args)
{
    Component& component = get_store<Component>().create(entity.id_.index, std::forward<Args>(args)...);
    entity.mask().set(get_component_id<Component>());
    return component;
}

template<typename Component, typename... Args>
Component director_t::create_temp_component(Args&&... args)
{
    if constexpr (std::is_constructible_v<Component, Args...>)
        return Component(std::forward<Args>(args)...);

    if constexpr (std::is_base_of_v<internal::base_property_t, Component>)
    {
        static_assert(sizeof...(Args) == 1, "Only one argument per property");
        auto temp = typename Component::value_type(std::forward<Args>(args)...);
        return *reinterpret_cast<Component*>(&temp);
    }

    return Component{ std::forward<Args>(args)... };
}

template<typename Component>
void director_t::remove_component(entity_t& entity)
{
    get_store<Component>().remove(entity.id_.index);
}

template<typename Component>
void director_t::remove_component_fast(entity_t& entity)
{
    get_store_fast<Component>().remove(entity.id_.index);
}

template<typename Component, typename... Args>
Component& director_t::set_component(entity_t& entity, Args&&... args)
{
    if (entity.has<Component>())
        return get_component_fast<Component>(entity) = create_temp_component<Component>(std::forward<Args>(args)...);
    return create_component<Component>(entity, std::forward<Args>(args)...);
}

template<typename Component, typename... Args>
Component& director_t::set_component_fast(entity_t& entity, Args&&... args)
{
    return get_component_fast<Component>(entity) = create_temp_component<Component>(std::forward<Args>(args)...);
}

template<typename... Components>
bool director_t::has_component(entity_t& entity)
{
    return has_component(entity, internal::component_mask<Components...>());
}

template<typename... Components>
bool director_t::has_component(const entity_t& entity) const
{
    return has_component(entity, internal::component_mask<Components...>());
}
} // namespace eden::ecs
