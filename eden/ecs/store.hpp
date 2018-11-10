
#pragma once

#include "mask.hpp"
#include "pool.hpp"

namespace eden::ecs
{
class director_t;

struct base_store_t
{
    virtual ~base_store_t(){};
    virtual void remove(uint32_t index) = 0;
    virtual void* get_void_ptr(uint32_t index) = 0;
    virtual const void* get_void_ptr(uint32_t index) const = 0;
    virtual void ensure_min_size(uint32_t size) = 0;
    virtual mask_t mask() const = 0;
};

template<typename Component>
class store : public base_store_t
{
public:
    store(director_t& director, size_t chunk_size = 64);

    template<typename... Args>
    Component& create(uint32_t index, Args&&... args);

    void remove(index_t index);

    Component& operator[](index_t index);
    Component& get(index_t index);
    Component const& get(index_t index) const;

    Component* get_ptr(index_t index);
    Component const* get_ptr(index_t index) const;

    void* get_void_ptr(index_t index);
    void const* get_void_ptr(index_t index) const;

    void ensure_min_size(index_t size);

    mask_t mask() const;

private:
    template<typename... Args>
    Component* create_component(void* ptr, Args&&... args);

    director_t& director;
    internal::pool<Component> pool;
};
} // namespace eden::ecs

#include "store.inl"
