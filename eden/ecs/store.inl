
// #include "director.hpp"

// namespace eden::ecs
// {
// template<typename Component>
// template<typename... Args>
// Component* store<Component>::create_component(void* ptr, Args&&... args)
// {
//     return new (ptr) Component(std::forward<Args>(args)...);
// }

// template<typename Component>
// template<typename... Args>
// Component& store<Component>::create(uint32_t index, Args&&... args)
// {
//     pool.ensure_min_size(index + 1);
//     auto c = create_component(pool.get_ptr(index), std::forward<Args>(args)...);
//     return *c;
// }

// template<typename Component>
// store<Component>::store(director_t& director, size_t chunk_size)
//     : director(director)
//     , pool(chunk_size)
// {
// }

// template<typename Component>
// void store<Component>::remove(index_t index)
// {
//     pool.destroy(index);
// }

// template<typename Component>
// Component& store<Component>::operator[](index_t index)
// {
//     return get(index);
// }

// template<typename Component>
// Component& store<Component>::get(index_t index)
// {
//     return *get_ptr(index);
// }

// template<typename Component>
// Component const& store<Component>::get(index_t index) const
// {
//     return *get_ptr(index);
// }

// template<typename Component>
// Component* store<Component>::get_ptr(index_t index)
// {
//     return pool.get_ptr(index);
// }

// template<typename Component>
// Component const* store<Component>::get_ptr(index_t index) const
// {
//     return pool.get_ptr(index);
// }

// template<typename Component>
// void* store<Component>::get_void_ptr(index_t index)
// {
//     return pool.get_ptr(index);
// }

// template<typename Component>
// void const* store<Component>::get_void_ptr(index_t index) const
// {
//     return pool.get_ptr(index);
// }

// template<typename Component>
// void store<Component>::ensure_min_size(index_t size)
// {
//     pool.ensure_min_size(size);
// }

// template<typename Component>
// mask_t store<Component>::mask() const
// {
//     return internal::component_mask<Component>();
// }
// } // namespace eden::ecs
