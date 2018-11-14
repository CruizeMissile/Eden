
#include "director.hpp"
#include <utility>

namespace eden::ecs
{
template<typename C, typename... Args>
C& entity_t::add(Args&&... args)
{
    return director_->create_component<C>(*this, std::forward<Args>(args)...);
}

template<typename C, typename... Args>
C& entity_t::set(Args&&... args)
{
    return director_->set_component<C>(*this, std::forward<Args>(args)...);
}

template<typename C>
C& entity_t::get()
{
    return director_->get_component<C>(*this);
}

template<typename C>
const C& entity_t::get() const
{
    return director_->get_component<C>(*this);
}


template<typename C>
bool entity_t::has() const
{
    return director_->has_component<C>(*this);
}

template<typename C>
void entity_t::remove()
{
    director_->remove_component<C>(*this);
}
} // namespace eden::ecs
