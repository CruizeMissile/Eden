
#pragma once

#include "entity.hpp"
#include "id.hpp"
#include "mask.hpp"

namespace eden::ecs
{
namespace internal
{
    // Used to for compile type type checking to see if type is a archetype
    struct base_archetype_t
    {};

    template<typename Type>
    constexpr bool is_archetype();

    template<typename Type, typename... List>
    struct is_type_in_list;
} // namespace internal

class director_t;

template<typename... Components>
class archetype : public internal::base_archetype_t
{
public:
    using this_type = archetype<Components...>;

    archetype(const entity_t entity);

    operator entity_t&();
    operator const entity_t&() const;

    template<typename Component>
    Component& get();

    template<typename Component>
    bool has();

    template<typename Component, typename... Args>
    Component& set(Args&&... args);

    template<typename Component, typename... Args>
    Component& add(Args&&... args);

    template<typename Component>
    void remove();
    void remove_all();
    void destroy();

    bool operator==(const entity_t& rhs) const;
    bool operator!=(const entity_t& rhs) const;

    id_t id();
    const id_t id() const;

    mask_t mask();
    const mask_t mask() const;

    bool is_valid() const;

protected:
    archetype();

    director_t& director();
    const director_t& director() const;

    entity_t& entity();
    const entity_t& entity() const;

private:
    template<typename C0, typename Arg>
    void init_components(Arg arg);

    template<typename C0, typename C1, typename... Cs, typename Arg0, typename Arg1, typename... Args>
    void init_components(Arg0 arg0, Arg1 arg1, Args... args);

    // Recursion init components without argument
    template<typename C>
    void init_components();

    template<typename C0, typename C1, typename... Cs>
    void init_components();

    template<typename... Args>
    void init(Args... args);

    static constexpr mask_t static_mask();

    union
    {
        director_t* director_;
        entity_t entity_;
    };

    friend class director_t;
    friend struct entity_t;
};
} // namespace eden::ecs

#include "archetype.inl"
