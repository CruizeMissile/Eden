
namespace eden::ecs
{
template<typename Type>
property<Type>::property()
{
}

template<typename Type>
property<Type>::property(const Type& value)
    : value(value)
{
}

template<typename Type>
property<Type>::operator Type&()
{
    return value;
}

template<typename Type>
property<Type>::operator const Type&() const
{
    return value;
}

template<typename Type>
template<typename Other>
bool property<Type>::operator==(const Other& rhs)
{
    return value == rhs;
}

template<typename Type>
template<typename Other>
bool property<Type>::operator!=(const Other& rhs)
{
    return value != rhs;
}

template<typename Type>
template<typename Other>
bool property<Type>::operator>=(const Other& rhs)
{
    return value >= rhs;
}

template<typename Type>
template<typename Other>
bool property<Type>::operator>(const Other& rhs)
{
    return value > rhs;
}

template<typename Type>
template<typename Other>
bool property<Type>::operator<=(const Other& rhs)
{
    return value <= rhs;
}

template<typename Type>
template<typename Other>
bool property<Type>::operator<(const Other& rhs)
{
    return value < rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator+=(const Other& rhs)
{
    return value += rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator-=(const Other& rhs)
{
    return value -= rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator*=(const Other& rhs)
{
    return value *= rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator/=(const Other& rhs)
{
    return value /= rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator%=(const Other& rhs)
{
    return value %= rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator&=(const Other& rhs)
{
    return value &= rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator|=(const Other& rhs)
{
    return value |= rhs;
}

template<typename Type>
template<typename Other>
Type& property<Type>::operator^=(const Other& rhs)
{
    return value ^= rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator+(const Other& rhs)
{
    return value + rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator-(const Other& rhs)
{
    return value - rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator*(const Other& rhs)
{
    return value * rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator/(const Other& rhs)
{
    return value / rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator%(const Other& rhs)
{
    return value % rhs;
}

template<typename Type>
Type& property<Type>::operator++()
{
    ++value;
    return value;
}

template<typename Type>
Type property<Type>::operator++(int)
{
    value_type copy = value;
    ++value;
    return copy;
}

template<typename Type>
Type& property<Type>::operator--()
{
    --value;
    return value;
}

template<typename Type>
Type property<Type>::operator--(int)
{
    value_type copy = value;
    --value;
    return copy;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator&(const Other& rhs)
{
    return value & rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator|(const Other& rhs)
{
    return value | rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator^(const Other& rhs)
{
    return value ^ rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator~()
{
    return ~value;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator>>(const Other& rhs)
{
    return value >> rhs;
}

template<typename Type>
template<typename Other>
Type property<Type>::operator<<(const Other& rhs)
{
    return value << rhs;
}
} // namespace eden::ecs
