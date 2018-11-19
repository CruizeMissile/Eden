
#include "director.hpp"
#include "mask.hpp"

namespace eden::ecs
{
template<typename Type>
view<Type>::view(director_t* director, mask_t mask)
: director_(director)
, mask_(mask)
{
}

template<typename Type>
typename view<Type>::iterator view<Type>::begin()
{
    return view<Type>::iterator(director_, mask_, true);
}

template<typename Type>
typename view<Type>::iterator view<Type>::end()
{
    return view<Type>::iterator(director_, mask_, false);
}

template<typename Type>
typename view<Type>::const_iterator view<Type>::begin()
{
    return view<Type>::iterator(director_, mask_, true);
}

template<typename Type>
typename view<Type>::const_iterator view<Type>::end()
{
    return view<Type>::iterator(director_, mask_, false);
}

template<typename Type>
template<typename... Components>
view<Type>&& view<Type>::with()
{
    mask_ |= internal::component_mask<Components...>();
    return *this;
}

template<typename Type>
index_t view<Type>::count()
{
    index_t count = 0;
    for (auto it = begin(); it != end(); ++it)
        ++count;

    return count;
}
}
