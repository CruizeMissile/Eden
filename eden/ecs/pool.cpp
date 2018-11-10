
#include "pool.hpp"

namespace eden::ecs::internal
{
base_pool::base_pool(size_t element_size, size_t chunk_size)
    : element_size_(element_size)
    , chunk_size_(chunk_size)
{
}

base_pool::~base_pool()
{
    for (uint8_t* chunk : chunks_)
        delete[] chunk;
}

index_t base_pool::size() const noexcept
{
    return size_;
}
index_t base_pool::capacity() const noexcept
{
    return capacity_;
}
size_t base_pool::chunks() const noexcept
{
    return chunks_.size();
}

void base_pool::ensure_min_size(size_t min_size)
{
    if (min_size >= size_)
    {
        if (min_size >= capacity_)
            ensure_min_capacity(min_size);
        size_ = min_size;
    }
}

void base_pool::ensure_min_capacity(size_t min_size)
{
    while (min_size >= capacity_)
    {
        uint8_t* chunk = new uint8_t[element_size_ * chunk_size_];
        chunks_.push_back(chunk);
        capacity_ += chunk_size_;
    }
}
} // namespace eden::ecs::internal
