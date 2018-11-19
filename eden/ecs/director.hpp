
#pragma once

#include "defines.hpp"
#include "id.hpp"
#include "mask.hpp"
#include <type_traits>
#include <vector>

namespace eden::ecs
{
namespace internal
{
    struct base_store_t;
    struct base_archetype_t;
    struct base_property_t;

    template<size_t, typename...>
    struct with_t;
} // namespace internal

template<typename...>
class archetype;
template<typename>
class entity_iterator;
template<typename>
class store;
template<typename>
class view;
struct entity_t;

class director_t
{
public:
    director_t(size_t chunk_size = 8192);
    ~director_t();

    entity_t create();
    std::vector<entity_t> create(const size_t num_of_entities);

    template<typename Lambda>
    void create(const size_t n, Lambda lambda);

    // Create an archetype
    template<typename Archetype, typename... Args>
    auto create(Args&&... args) ->
        typename std::enable_if_t<std::is_base_of_v<internal::base_archetype_t, Archetype> ||
            std::is_base_of_v<entity_t, Archetype>, Archetype&>;

    // Create an entity with components assigned
    template<typename... Components, typename... Args>
    auto create_with(Args&&... args) ->
        typename std::conditional<(sizeof...(Components) > 0), archetype<Components...>, archetype<Args...>>::type;

    // Create an entiyt with components assigned, using default values
    template<typename... Components>
    archetype<Components...> create_with();

    // Access a view of all entities with the components given in the template
    template<typename... Components>
    view<archetype<Components...>> with();

    // Iterate through all entities with all component that are specified in teh lambda parameters
    template<typename Lambda>
    void with(Lambda lambda);

    // Access a view of all entites that has all components in the archetype
    template<typename Archetype>
    view<Archetype> fetch_every();

    // Access a view of all entities that have all components in the archetype specified as a lambda param
    template<typename Lambda>
    void fetch_every(Lambda lambda);

    entity_t operator[](index_t index);
    entity_t operator[](id_t id);

    size_t count();

private:
    index_t find_new_entity_index();
    void create_new_block(index_t next_free_index);

    template<typename Component, typename... Args>
    store<Component>& create_store(Args&&... args);

    template<typename Component>
    store<Component>& get_store_fast();
    template<typename Component>
    store<const Component>& get_store_fast() const;

    template<typename Component>
    store<Component>& get_store();
    template<typename Component>
    const store<Component>& get_store() const;

    internal::base_store_t& get_store(size_t component_index);
    const internal::base_store_t& get_store(size_t component_index) const;

    template<typename Component>
    Component& get_component(entity_t& entity);
    template<typename Component>
    const Component& get_component(const entity_t& entity) const;

    template<typename Component>
    Component& get_component_fast(index_t index);
    template<typename Component>
    const Component& get_component_fast(index_t index) const;
    template<typename Component>
    Component& get_component_fast(entity_t& entity);
    template<typename Component>
    const Component& get_component_fast(const entity_t& entity) const;

    template<typename Component, typename... Args>
    Component& create_component(entity_t& entity, Args&&... args);

    template<typename Component, typename... Args>
    Component create_temp_component(Args&&... args);

    template<typename Component>
    void remove_component(entity_t& entity);

    template<typename Component>
    void remove_component_fast(entity_t& entity);
    void remove_all_components(entity_t& entity);
    void clear_mask(entity_t& entity);

    template<typename Component, typename... Args>
    Component& set_component(entity_t& entity, Args&&... args);

    template<typename Component, typename... Args>
    Component& set_component_fast(entity_t& entity, Args&&... args);

    template<typename... Components>
    bool has_component(entity_t& entity);
    template<typename... Components>
    bool has_component(const entity_t& entity) const;
    bool has_component(entity_t& entity, mask_t component_mask);
    bool has_component(const entity_t& entity, const mask_t& component_mask) const;

    bool is_valid(entity_t& entity);
    bool is_valid(const entity_t& entity) const;

    void destroy(entity_t& entity);

    mask_t& mask(entity_t& entity);
    const mask_t& mask(const entity_t& entity) const;
    mask_t& mask(index_t index);
    const mask_t& mask(index_t index) const;

    entity_t get_entity(id_t id);
    entity_t get_entity(index_t index);

    // Gey how many entities the director_t can handle atm
    size_t capacity() const;

    std::vector<internal::base_store_t*> stores_;
    std::vector<index_t> block_index_;
    std::vector<index_t> free_list_;
    std::vector<index_t> next_free_indexes_;
    std::vector<mask_t> masks_;
    std::vector<size_t> index_to_component_mask_;
    std::vector<version_t> versions_;

    index_t block_count_ = 0;
    index_t count_ = 0;

    template<typename... Components>
    friend class archetype;
    template<typename>
    friend class entity_iterator;
    template<typename Component>
    friend class store;
    friend struct entity_t;
};
} // namespace eden::ecs

#include "director.inl"
