
#include "entity.hpp"

namespace eden::ecs
{
bool entity_t::has(mask_t mask) const
{
    return director_->mask(*this) == mask;
}

void entity_t::destroy()
{
    director_->destroy(*this);
}

mask_t& entity_t::mask()
{
    return director_->mask(*this);
}

const mask_t& entity_t::mask() const
{
    return director_->mask(*this);
}

id_t& entity_t::id()
{
    return id_;
}

const id_t& entity_t::id() const
{
    return id_;
}
} // namespace eden::ecs
