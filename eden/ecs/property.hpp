
#pragma once

namespace eden::ecs
{
namespace internal
{
    struct base_property
    {};
} // namespace internal

template<typename Type>
struct property : internal::base_property
{
    using value_type = Type;

    property();
    property(const Type& value);

    operator Type&();
    operator const Type&() const;

    Type value;

    template<typename Other>
    bool operator==(const Other& rhs);
    template<typename Other>
    bool operator!=(const Other& rhs);
    template<typename Other>
    bool operator>=(const Other& rhs);
    template<typename Other>
    bool operator>(const Other& rhs);
    template<typename Other>
    bool operator<=(const Other& rhs);
    template<typename Other>
    bool operator<(const Other& rhs);

    template<typename Other>
    Type& operator+=(const Other& rhs);
    template<typename Other>
    Type& operator-=(const Other& rhs);
    template<typename Other>
    Type& operator*=(const Other& rhs);
    template<typename Other>
    Type& operator/=(const Other& rhs);
    template<typename Other>
    Type& operator%=(const Other& rhs);
    template<typename Other>
    Type& operator&=(const Other& rhs);
    template<typename Other>
    Type& operator|=(const Other& rhs);
    template<typename Other>
    Type& operator^=(const Other& rhs);

    template<typename Other>
    Type operator+(const Other& rhs);
    template<typename Other>
    Type operator-(const Other& rhs);
    template<typename Other>
    Type operator*(const Other& rhs);
    template<typename Other>
    Type operator/(const Other& rhs);
    template<typename Other>
    Type operator%(const Other& rhs);
    Type& operator++();
    Type operator++(int);
    Type& operator--();
    Type operator--(int);

    template<typename Other>
    Type operator&(const Other& rhs);
    template<typename Other>
    Type operator|(const Other& rhs);
    template<typename Other>
    Type operator^(const Other& rhs);
    template<typename Other>
    Type operator~();
    template<typename Other>
    Type operator>>(const Other& rhs);
    template<typename Other>
    Type operator<<(const Other& rhs);
};
} // namespace eden::ecs

#include "property.inl"
