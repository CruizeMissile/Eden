
#pragma once

#include "id.hpp"
#include "mask.hpp"

namespace eden::ecs
{
class director_t;

struct entity_t
{
    template<typename C, typename... Args>
    C& add(Args&&... args);

    template<typename C, typename... Args>
    C& set(Args&&... args);

    template<typename C>
    C& get() const;

    template<typename C>
    bool has() const;

    void destroy();

    mask_t& mask();
    const mask_t& mask() const;

    id_t id_;
    director_t* director_;

private:
    friend class director_t;
    entity_t(director_t* director, id_t id)
        : director_(director)
        , id_(id)
    {}
};

} // namespace eden::ecs

#include "entity.inl"
