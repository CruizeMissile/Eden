
#include "system.hpp"
#include "dispatcher.hpp"

namespace eden::ecs
{
director_t& system_t::director()
{
    return *dispatcher_->director_;
}
} // namespace eden::ecs
