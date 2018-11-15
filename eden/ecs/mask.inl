
#include <algorithm>
#include <iostream>

namespace eden::ecs
{
template<size_t BlockSize>
bitmask<BlockSize>::bitmask() noexcept
{
    auto size = (0 + BlockSize - 1) / BlockSize;
    check_capacity(size);
}

template<size_t BlockSize>
bitmask<BlockSize>::bitmask(size_type value) noexcept
{
    // https://stackoverflow.com/a/2249738
    auto n_bits_index = get_highest_bit_count(value);
    auto index = n_bits_index / BlockSize;
    check_capacity(index);
    while (n_bits_index != 0)
    {
        auto r = (value >> n_bits_index) & 1;
        if (r == 1)
            bits_[0].set(n_bits_index);
        n_bits_index--;
    }

    auto r = (value >> n_bits_index) & 1;
    if (r == 1)
        bits_[0].set(index);
}

template<size_t BlockSize>
bitmask<BlockSize>::~bitmask()
{

}

template<size_t BlockSize>
void bitmask<BlockSize>::check_capacity(size_t n)
{
    if (n >= bits_.size())
        bits_.resize(n + 1, 0);
}

template<size_t BlockSize>
constexpr size_t bitmask<BlockSize>::get_highest_bit_count(size_t value)
{
    if (value == 0)
        return 0;

    // https://stackoverflow.com/a/4970859
    size_t result = 1;
    while (value >>= 1)
        ++result;
    return result;
}


template<size_t BlockSize>
bitmask<BlockSize> bitmask<BlockSize>::operator&(const bitmask<BlockSize>& rhs)
{
    bitmask<BlockSize> copy = *this;
    return (copy &= rhs);
}

template<size_t BlockSize>
bitmask<BlockSize> bitmask<BlockSize>::operator|(const bitmask<BlockSize>& rhs)
{
    bitmask<BlockSize> copy = *this;
    return (copy |= rhs);
}

template<size_t BlockSize>
bitmask<BlockSize> bitmask<BlockSize>::operator^(const bitmask<BlockSize>& rhs)
{
    bitmask<BlockSize> copy = *this;
    return (copy ^= rhs);
}

template<size_t BlockSize>
bitmask<BlockSize>& bitmask<BlockSize>::operator&=(const bitmask<BlockSize>& rhs)
{
    auto min = std::min(bits_.size(), rhs.bits_.size());
    for (size_t i = 0 ; i < min; ++i)
        bits_[i] &= rhs.bits_[i];
    return *this;
}

template<size_t BlockSize>
bitmask<BlockSize>& bitmask<BlockSize>::operator|=(const bitmask<BlockSize>& rhs)
{
    auto min = std::min(bits_.size(), rhs.bits_.size());
    for (size_t i = 0 ; i < min; ++i)
        bits_[i] |= rhs.bits_[i];
    return *this;
}

template<size_t BlockSize>
bitmask<BlockSize>& bitmask<BlockSize>::operator^=(const bitmask<BlockSize>& rhs)
{
    auto min = std::min(bits_.size(), rhs.bits_.size());
    for (size_t i = 0 ; i < min; ++i)
        bits_[i] ^= rhs.bits_[i];

    return *this;
}

template<size_t BlockSize>
bool bitmask<BlockSize>::operator==(const bitmask<BlockSize>& rhs)
{
    return true;
}

template<size_t BlockSize>
bool bitmask<BlockSize>::operator!=(const bitmask<BlockSize>& rhs)
{
    return true;

}
}
