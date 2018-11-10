

namespace eden::ecs::internal
{
template<typename Type>
pool<Type>::pool(size_t chunk_size)
    : base_pool(sizeof(Type), chunk_size)
{}

template<typename Type>
void pool<Type>::destroy(index_t index)
{
    Type* ptr = get_ptr(index);
    ptr->~Type();
}

template<typename Type>
Type* pool<Type>::get_ptr(index_t index)
{
    return reinterpret_cast<Type*>(chunks_[index / chunk_size_] + (index % chunk_size_) * element_size_);
}

template<typename Type>
const Type* pool<Type>::get_ptr(index_t index) const
{
    return reinterpret_cast<Type*>(chunks_[index / chunk_size_] + (index % chunk_size_) * element_size_);
}

template<typename Type>
Type& pool<Type>::get(index_t index)
{
    return *get_ptr(index);
}

template<typename Type>
const Type& pool<Type>::get(index_t index) const
{
    return *get_ptr(index);
}
} // namespace eden::ecs::internal
