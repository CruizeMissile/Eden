
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
} // namespace internal

struct entity_t;
template<typename T>
class store;
template<typename... Components>
class archetype;

class director_t
{
public:
    director_t(size_t chunk_size = 8192);
    ~director_t();

    entity_t create();
    std::vector<entity_t> create(const size_t num_of_entities);

    // Create an archetype
    template<typename Archetype, typename... Args>
    auto create(Args&&... args) -> typename std::enable_if_t<
        std::is_base_of_v<internal::base_archetype_t, Archetype> || std::is_base_of_v<entity_t, Archetype>, Archetype&>;

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
    template<typename Component>
    friend class store;
    friend struct entity_t;
};
} // namespace eden::ecs

#include "director.inl"
