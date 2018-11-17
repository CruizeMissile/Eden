
#include "director.hpp"
#include <utility>

namespace eden::ecs
{
template<typename Component, typename... Args>
Component& entity_t::add(Args&&... args)
{
    return director_->create_component<Component>(*this, std::forward<Args>(args)...);
}

template<typename Component, typename... Args>
Component& entity_t::set(Args&&... args)
{
    return director_->set_component<Component>(*this, std::forward<Args>(args)...);
}

template<typename Component>
Component& entity_t::get()
{
    return director_->get_component<Component>(*this);
}

template<typename Component>
const Component& entity_t::get() const
{
    return director_->get_component<Component>(*this);
}

template<typename... Component>
bool entity_t::has() const
{
    return director_->has_component<Component...>(*this);
}

template<typename Component>
void entity_t::remove()
{
    director_->remove_component<Component>(*this);
}
} // namespace eden::ecs
