
#include "director.hpp"

namespace eden::ecs
{
template<typename Type>
entity_iterator<Type>::entity_iterator(director_t* director, mask_t mask, bool begin)
: director_(director)
, mask_(mask)
, cursor_(0)
{
    size_ = director_->versions_.size();
    if (!begin)
        cursor_ = size_;
    find_next();
}

template<typename Type>
entity_iterator<Type>::entity_iterator(const entity_iterator& it)
: entity_iterator(it.director_, it.cursor_)
{
}

template<typename Type>
index_t entity_iterator<Type>::index() const
{
    return cursor_;
}

template<typename Type>
entity_iterator<Type>& entity_iterator<Type>::operator++()
{
    ++cursor_;
    find_next();
    return *this;
}

template<typename Type>
Type entity_iterator<Type>::entity()
{
    return director_->get_entity(index()).template as<typename entity_iterator<Type>::ref_remove>();
}

template<typename Type>
const Type entity_iterator<Type>::entity() const
{
    return director_->get_entity(index()).template as<typename entity_iterator<Type>::ref_remove>();
}

template<typename Type>
void entity_iterator<Type>::find_next()
{
    while (cursor_ < size_ && (director_->masks_[cursor_] & mask_) != mask_)
        ++cursor_;
}

template<typename Type>
bool operator==(entity_iterator<Type> const &lhs, entity_iterator<Type> const &rhs)
{
    return lhs.index() == rhs.index();
}

template<typename Type>
bool operator!=(entity_iterator<Type> const &lhs, entity_iterator<Type> const &rhs)
{
    return !(lhs == rhs);
}

template<typename Type>
inline Type operator*(entity_iterator<Type> &lhs)
{
    return lhs.entity();
}

template<typename Type>
inline Type const &operator*(entity_iterator<Type> const &lhs)
{
    return lhs.entity();
}
}
