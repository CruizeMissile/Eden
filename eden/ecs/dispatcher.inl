
#include "defines.hpp"
#include "system.hpp"
#include <utility>

namespace eden::ecs
{
template<typename System, typename... Args>
System& dispatcher_t::add(Args&&... args)
{
    auto index = get_system_id<System>();
    systems_.resize(index + 1);
    System* sys = new System(std::forward<Args>(args)...);
    sys->dispatcher_ = this;
    systems_[index] = sys;
    order_.push_back(index);
    return *sys;
}

template<typename System>
void dispatcher_t::remove()
{
    auto index = get_system_id<System>();
    delete systems_[index];
    systems_[index] = nullptr;
    for (auto it = order_.begin(); it != order_.end(); ++it)
    {
        if (*it == index)
        {
            order_.erase(it);
            break;
        }
    }
}

template<typename System>
bool dispatcher_t::exists()
{
    auto index = get_system_id<System>();
    return systems_.size() > index && systems_[index] != nullptr;
}

} // namespace eden::ecs
