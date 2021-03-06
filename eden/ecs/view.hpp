
#pragma once

namespace eden::ecs
{
template<typename Type>
class entity_iterator;

class director_t;

template<typename Type>
class view
{
public:
    using iterator = entity_iterator<Type>;
    using const_iterator = entity_iterator<const Type&>;

    view(director_t* director, mask_t mask);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    template<typename... Components>
    view<Type>&& with();

    index_t count();

private:
    director_t* director_;
    mask_t mask_;

    friend class director_t;
};
} // namespace eden::ecs

#include "view.inl"
