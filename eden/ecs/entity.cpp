
#include "entity.hpp"

namespace eden::ecs
{
entity_t::entity_t(director_t* director, id_t id)
    : director_(director)
    , id_(id)
{}

bool entity_t::has(mask_t mask) const
{
    return director_->has_component(*this, mask);
}

void entity_t::remove_all()
{
    director_->remove_all_components(*this);
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

bool entity_t::is_valid()
{
    return director_->is_valid(*this);
}

bool entity_t::is_valid() const
{
    return director_->is_valid(*this);
}
} // namespace eden::ecs
