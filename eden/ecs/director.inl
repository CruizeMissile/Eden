
#include "entity.hpp"
#include "store.hpp"

namespace eden::ecs
{
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
        return get_component_fast<Component>(entity) = create_tmp_component<Component>(std::forward<Args>(args)...);
    return create_component<Component>(entity, std::forward<Args>(args)...);
}

template<typename Component, typename... Args>
Component& director_t::set_component_fast(entity_t& entity, Args&&... args)
{
    return get_component_fast<Component>(entity) = create_tmp_component<Component>(std::forward<Args>(args)...);
}

template<typename... Components>
bool director_t::has_component(entity_t& entity)
{
    return has_component(entity, details::component_mask<Components...>());
}

template<typename... Components>
bool director_t::has_component(const entity_t& entity) const
{
    return has_component(entity, details::component_mask<Components...>());
}
} // namespace eden::ecs
