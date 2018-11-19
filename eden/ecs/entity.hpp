
#pragma once

#include "id.hpp"
#include "mask.hpp"

namespace eden::ecs
{
template<typename...>
class archetype;
class director_t;

struct entity_t
{
    template<typename Component, typename... Args>
    Component& add(Args&&... args);

    template<typename Component, typename... Args>
    Component& set(Args&&... args);

    template<typename Component>
    Component& get();
    template<typename Component>
    const Component& get() const;

    template<typename... Component>
    bool has() const;
    bool has(mask_t mask) const;

    template<typename Archetype>
    Archetype& as();
    template<typename Archetype>
    const Archetype& as() const;

    template<typename... Components>
    archetype<Components...>& assume();
    template<typename... Components>
    const archetype<Components...>& assume() const;

    template<typename Component>
    void remove();

    void remove_all();
    void destroy();

    mask_t& mask();
    const mask_t& mask() const;

    id_t& id();
    const id_t& id() const;

    bool is_valid();
    bool is_valid() const;

private:
    director_t* director_;
    id_t id_;

private:
    friend class director_t;
    entity_t(director_t* director, id_t id);
};

} // namespace eden::ecs

#include "entity.inl"
