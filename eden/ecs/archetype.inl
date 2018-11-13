

#include "director.hpp"
#include "entity.hpp"
#include "utils.hpp"
#include <type_traits>
#include <utility>

namespace eden::ecs::internal
{
template<typename Type>
constexpr bool is_archetype()
{
    return std::is_base_of_v<base_archetype_t, Type>;
}

template<typename Type, typename... List>
struct is_type_in_list<Type, Type, List...> : std::true_type
{};

template<typename Type>
struct is_type_in_list<Type, Type> : std::true_type
{};

template<typename Type, typename End>
struct is_type_in_list<Type, End> : std::false_type
{};

template<typename Type, typename Next, typename... List>
struct is_type_in_list<Type, Next, List...> : is_type_in_list<Type, List...>::type
{};
} // namespace eden::ecs::internal

namespace eden::ecs
{
template<typename... Components>
archetype<Components...>::archetype()
{
}

template<typename... Components>
archetype<Components...>::archetype(const entity_t entity)
    : entity_(entity)
{
}

template<typename... Components>
archetype<Components...>::operator entity_t&()
{
    return entity_;
}

template<typename... Components>
archetype<Components...>::operator const entity_t&() const
{
    return entity_;
}

template<typename... Components>
template<typename Component>
Component& archetype<Components...>::get()
{
    return director_->get_component<Component>(entity_);
}

template<typename... Components>
template<typename Component>
bool archetype<Components...>::has()
{
    return director_->has_component<Component>(entity_);
}

template<typename... Components>
template<typename Component, typename... Args>
Component& archetype<Components...>::set(Args&&... args)
{
    return director_->set_component<Component>(entity_, std::forward<Args...>(args)...);
}

template<typename... Components>
template<typename Component, typename... Args>
Component& archetype<Components...>::add(Args&&... args)
{
    return director_->set_component<Component>(entity_, std::forward<Args...>(args)...);
}

template<typename... Components>
template<typename Component>
void archetype<Components...>::remove()
{
    director_->remove_component<Component>(entity_);
}

template<typename... Components>
void archetype<Components...>::remove_all()
{
    director().remove_all_components(entity_);
}

template<typename... Components>
void archetype<Components...>::destroy()
{
    director().destroy(entity_);
}

template<typename... Components>
bool archetype<Components...>::operator==(const entity_t& rhs) const
{
    return entity() == rhs;
}

template<typename... Components>
bool archetype<Components...>::operator!=(const entity_t& rhs) const
{
    return entity() != rhs;
}

template<typename... Components>
id_t archetype<Components...>::id()
{
    return entity().id();
}

template<typename... Components>
const id_t archetype<Components...>::id() const
{
    return entity_.id();
}

template<typename... Components>
bool archetype<Components...>::is_valid() const
{
    return entity_.is_valid();
}

template<typename... Components>
template<typename C0, typename Arg>
inline void archetype<Components...>::init_components(Arg arg)
{
    add<C0>(arg);
}

template<typename... Components>
template<typename C0, typename C1, typename... Cs, typename Arg0, typename Arg1, typename... Args>
inline void archetype<Components...>::init_components(Arg0 arg0, Arg1 arg1, Args... args)
{
    init_components<C0>(arg0);
    init_components<C1, Cs...>(arg1, args...);
}
// Recursion init components without argument
template<typename... Components>
template<typename C>
inline void archetype<Components...>::init_components()
{
    add<C>();
}

template<typename... Components>
template<typename C0, typename C1, typename... Cs>
inline void archetype<Components...>::init_components()
{
    init_components<C0>();
    init_components<C1, Cs...>();
}

template<typename... Components>
template<typename... Args>
inline void archetype<Components...>::init(Args... args)
{
    init_components<Components...>(args...);
}

template<typename... Components>
constexpr mask_t archetype<Components...>::static_mask()
{
    return internal::component_mask<Components...>();
}

template<typename... Components>
director_t& archetype<Components...>::director()
{
    return *director_;
}

template<typename... Components>
const director_t& archetype<Components...>::director() const
{
    return *director_;
}

template<typename... Components>
entity_t& archetype<Components...>::entity()
{
    return entity_;
}

template<typename... Components>
const entity_t& archetype<Components...>::entity() const
{
    return entity_;
}

template<typename... Components>
mask_t archetype<Components...>::mask()
{
    return director_->mask(entity_);
}

template<typename... Components>
const mask_t archetype<Components...>::mask() const
{
    return director_->mask(entity_);
}
} // namespace eden::ecs
