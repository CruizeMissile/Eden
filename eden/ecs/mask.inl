
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace eden::ecs
{
template<size_t BlockSize>
dynamic_bitset<BlockSize>::dynamic_bitset() noexcept
{
    auto size = (0 + BlockSize - 1) / BlockSize;
    check_capacity(size);
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>::dynamic_bitset(size_type value) noexcept
{
   // https://stackoverflow.com/a/2249738
   auto n_bits_index = get_highest_bit_count(value);
   if (n_bits_index == 0)
   {
       check_capacity(0);
       return;
   }

   --n_bits_index;
   auto index = n_bits_index / BlockSize;
   check_capacity(index);
   while (true)
   {
       auto r = (value >> n_bits_index) & 1;
       if (r == 1)
           bits_[0].set(n_bits_index);

       if (n_bits_index == 0)
           return;

       --n_bits_index;
   }
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>::~dynamic_bitset()
{
    bits_.clear();
}

template<size_t BlockSize>
bool dynamic_bitset<BlockSize>::operator[](size_type index) const
{
    auto chunk = index / BlockSize;
    if (chunk >= bits_.size())
        return false;

    index = index - (chunk * BlockSize);
    return bits_[chunk][index];
}

template<size_t BlockSize>
typename dynamic_bitset<BlockSize>::size_type dynamic_bitset<BlockSize>::count() const noexcept
{
    size_type r = 0;
    for (auto block : bits_)
        r += block.count();

    return r;
}

template<size_t BlockSize>
typename dynamic_bitset<BlockSize>::size_type dynamic_bitset<BlockSize>::size() noexcept
{
    size_type r = 0;
    for (auto& block : bits_)
        r += block.size();

    return r;
}

template<size_t BlockSize>
bool dynamic_bitset<BlockSize>::test(size_type index) const
{
    auto chunk = index / BlockSize;
    if (chunk >= bits_.size())
        throw std::out_of_range("index is out of range");

    index = index - (chunk * BlockSize);
    return bits_[chunk].test(index);
}

template<size_t BlockSize>
bool dynamic_bitset<BlockSize>::any() const noexcept
{
    for (auto& block : bits_)
        if (block.any())
            return true;

    return false;
}

template<size_t BlockSize>
bool dynamic_bitset<BlockSize>::none() const noexcept
{
    for (auto& block : bits_)
        if (!block.none())
            return false;

    return true;
}

template<size_t BlockSize>
bool dynamic_bitset<BlockSize>::all() const noexcept
{
    for (auto& block : bits_)
        if (!block.all())
            return false;

    return true;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::set() noexcept
{
    for (auto& block : bits_)
        block.set();

    return *this;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::set(size_type index, bool value)
{
    auto chunk = index / BlockSize;
    check_capacity(chunk);
    index = index - (chunk * BlockSize);
    bits_[chunk].set(index, value);
    return *this;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::reset() noexcept
{
    for (auto& block : bits_)
        block.reset();

    return *this;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::reset(size_type index)
{
    auto chunk = index / BlockSize;
    check_capacity(chunk);
    index = index - (chunk * BlockSize);
    bits_[chunk].reset(index);
    return *this;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::flip() noexcept
{
    for (auto& block : bits_)
        block.flip();

    return *this;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::flip(size_type index)
{
    auto chunk = index / BlockSize;
    check_capacity(chunk);
    index = index - (chunk * BlockSize);
    bits_[chunk].flip(index);
}

template<size_t BlockSize>
std::string dynamic_bitset<BlockSize>::to_string(char zero, char one)
{
    std::string s;
    for (auto& block : bits_)
        s += block.to_string(zero, one);

    return s;
}

template<size_t BlockSize>
void dynamic_bitset<BlockSize>::check_capacity(size_t n)
{
    if (n >= bits_.size())
        bits_.resize(n + 1, 0);
}

template<size_t BlockSize>
constexpr size_t dynamic_bitset<BlockSize>::get_highest_bit_count(size_t value)
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
dynamic_bitset<BlockSize> dynamic_bitset<BlockSize>::operator&(const dynamic_bitset<BlockSize>& rhs)
{
    dynamic_bitset<BlockSize> copy = *this;
    return (copy &= rhs);
}

template<size_t BlockSize>
dynamic_bitset<BlockSize> dynamic_bitset<BlockSize>::operator|(const dynamic_bitset<BlockSize>& rhs)
{
    dynamic_bitset<BlockSize> copy = *this;
    return (copy |= rhs);
}

template<size_t BlockSize>
dynamic_bitset<BlockSize> dynamic_bitset<BlockSize>::operator^(const dynamic_bitset<BlockSize>& rhs)
{
    dynamic_bitset<BlockSize> copy = *this;
    return (copy ^= rhs);
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::operator&=(const dynamic_bitset<BlockSize>& rhs)
{
    auto min = std::min(bits_.size(), rhs.bits_.size());
    for (size_t i = 0 ; i < min; ++i)
        bits_[i] &= rhs.bits_[i];

    return *this;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::operator|=(const dynamic_bitset<BlockSize>& rhs)
{
    auto min = std::min(bits_.size(), rhs.bits_.size());
    for (size_t i = 0 ; i < min; ++i)
        bits_[i] |= rhs.bits_[i];

    return *this;
}

template<size_t BlockSize>
dynamic_bitset<BlockSize>& dynamic_bitset<BlockSize>::operator^=(const dynamic_bitset<BlockSize>& rhs)
{
    auto min = std::min(bits_.size(), rhs.bits_.size());
    for (size_t i = 0 ; i < min; ++i)
        bits_[i] ^= rhs.bits_[i];

    return *this;
}

template<size_t BlockSize>
bool dynamic_bitset<BlockSize>::operator==(const dynamic_bitset<BlockSize>& rhs) const noexcept
{
    if (bits_.size() != rhs.bits_.size())
        return false;

    for (size_t i = 0 ; i < bits_.size(); ++i)
    {
        if (bits_[i] != rhs.bits_[i])
            return false;
    }

    return true;
}

template<size_t BlockSize>
bool dynamic_bitset<BlockSize>::operator!=(const dynamic_bitset<BlockSize>& rhs) const noexcept
{
    return !(*this == rhs);
}
}
