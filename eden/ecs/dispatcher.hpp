
#pragma once

#include <vector>

namespace eden::ecs
{
class director_t;
class system_t;

class dispatcher_t
{
public:
    dispatcher_t(director_t& director);
    ~dispatcher_t();

    template<typename System, typename... Args>
    System& add(Args&&... args);

    template<typename System>
    void remove();

    void update(float delta_time);

    template<typename System>
    bool exists();

private:
    std::vector<system_t*> systems_;
    std::vector<size_t> order_;
    director_t* director_;

    friend class system_t;
};
} // namespace eden::ecs

#include "dispatcher.inl"
