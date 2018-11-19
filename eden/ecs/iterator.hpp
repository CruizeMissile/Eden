
#pragma once

#include "mask.hpp"
#include <iterator>
#include <type_traits>

namespace eden::ecs
{
class director_t;

template<typename Type>
class entity_iterator : public std::iterator<
    std::input_iterator_tag,
    typename std::remove_reference<Type>::type
>
{
    using ref_remove = typename std::remove_reference<typename std::remove_const<Type>::type>::type;

public:
    entity_iterator(director_t* director, mask_t mask, bool begin = true);
    entity_iterator(const entity_iterator& it);
    entity_iterator& operator=(const entity_iterator& rhs) = default;

    index_t index() const;
    entity_iterator& operator++();

    Type entity();
    const Type entity() const;

private:
    void find_next();

    director_t* director_;
    mask_t mask_;
    index_t cursor_;
    size_t size_;
};

template<typename Type>
bool operator==(entity_iterator<Type> const &lhs, entity_iterator<Type> const &rhs);

template<typename Type>
bool operator!=(entity_iterator<Type> const &lhs, entity_iterator<Type> const &rhs);

template<typename Type>
inline Type operator*(entity_iterator<Type> &lhs);

template<typename Type>
inline Type const &operator*(entity_iterator<Type> const &lhs);

}

#include "iterator.inl"
