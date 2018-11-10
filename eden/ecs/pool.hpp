
#pragma once

#include "defines.hpp"
#include <vector>

namespace eden::ecs::internal
{
class base_pool
{
public:
    explicit base_pool(size_t element_size, size_t chunk_size = EDEN_DEFAULT_CHUNK_SIZE);
    virtual ~base_pool();

    base_pool(const base_pool&) = delete;
    base_pool& operator=(const base_pool&) = delete;

    inline index_t size() const noexcept;
    inline index_t capacity() const noexcept;
    inline size_t chunks() const noexcept;
    inline void ensure_min_size(size_t min_size);
    inline void ensure_min_capacity(size_t min_size);

    virtual void destroy(index_t index) = 0;

protected:
    index_t size_ = 0;
    index_t capacity_ = 0;
    size_t element_size_;
    size_t chunk_size_;
    std::vector<uint8_t*> chunks_;
};

template<typename Type>
class pool : public base_pool
{
public:
    pool(size_t chunk_size);
    void destroy(index_t index) override;

    Type* get_ptr(index_t index);
    const Type* get_ptr(index_t index) const;

    Type& get(index_t index);
    const Type& get(index_t index) const;

    Type& operator[](index_t index);
    const Type& operator[](index_t index) const;
};
} // namespace eden::ecs::internal

#include "pool.inl"
