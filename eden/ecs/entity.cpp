
#include "entity.hpp"

namespace eden::ecs
{
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
} // namespace eden::ecs
