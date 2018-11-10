
#include "dispatcher.hpp"

namespace eden::ecs
{
dispatcher_t::dispatcher_t(director_t& director)
    : director_(&director)
{
}

dispatcher_t::~dispatcher_t()
{
    for (auto sys : systems_)
    {
        if (sys != nullptr)
            delete sys;
    }

    systems_.clear();
    order_.clear();
}

void dispatcher_t::update(float delta_time)
{
    for (auto index : order_)
        systems_[index]->update(delta_time);
}
} // namespace eden::ecs
