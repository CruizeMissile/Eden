
#include "mask.hpp"

#include <algorithm>
#include <cstring>
#include <sstream>

namespace eden::ecs
{
mask_t::mask_t()
{
    data.reserve(1);
    clear();
}

mask_t::~mask_t()
{
    data.clear();
}

mask_t::mask_t(const mask_t& rhs)
{
    data = rhs.data;
}

mask_t::mask_t(mask_t&& rhs)
{
    data.swap(rhs.data);
}

mask_t::mask_t(data_type n_bits)
{
    data_type reserve = 1 + (n_bits >> 6);
    data.reserve(static_cast<size_t>(reserve));
    clear();
}

mask_t& mask_t::operator=(const mask_t& rhs)
{
    data = rhs.data;
    return *this;
}

mask_t& mask_t::operator=(mask_t&& rhs)
{
    data.swap(rhs.data);
    return *this;
}

bool mask_t::get(data_type index) const
{
    data_type word = index >> 6;
    if (word >= data.size())
        return false;

    return (data[static_cast<size_t>(word)] & (1ull << (index & 0x3F))) != 0ull;
}

bool mask_t::get_and_clear(data_type index)
{
    data_type word = index >> 6;
    if (word >= data.size())
        return false;

    uint64_t old = data[static_cast<size_t>(word)];
    data[static_cast<size_t>(word)] &= ~(1ull << (index & 0x3F));
    return data[static_cast<size_t>(word)] != old;
}

bool mask_t::get_and_set(data_type index)
{
    data_type word = index >> 6;
    check_capacity(word);
    uint64_t old = data[static_cast<size_t>(word)];
    data[static_cast<size_t>(word)] |= 1ull << (index & 0x3F);
    return data[static_cast<size_t>(word)] == old;
}

void mask_t::set(data_type index)
{
    data_type word = index >> 6;
    check_capacity(word);
    data[static_cast<size_t>(word)] |= 1ull << (index & 0x3F);
}

void mask_t::flip(data_type index)
{
    data_type word = index >> 6;
    check_capacity(word);
    data[static_cast<size_t>(word)] ^= 1ull << (index & 0x3F);
}

std::string mask_t::to_string() const
{
    std::ostringstream ss;

    data_type length = used_words();
    for (data_type i = 0; i < length; i++)
    {
        ss << data[static_cast<size_t>(i)];
        if (i + 1 != length)
            ss << ",";
    }

    return ss.str();
}

void mask_t::check_capacity(data_type len)
{
    if (len >= data.size())
    {
        len++;
        data.resize(static_cast<size_t>(len), 0);
    }
}

void mask_t::clear(data_type index)
{
    data_type word = index >> 6;
    if (word >= data.size())
        return;

    data[static_cast<size_t>(word)] &= ~(1ull << (index & 0x3F));
}

void mask_t::clear()
{
    memset(data.data(), 0, data.size() * sizeof(uint64_t));
}

mask_t::data_type mask_t::num_bits() const
{
    return data.size() << 6;
}

mask_t::data_type mask_t::used_words() const
{
    size_t word = data.size();
    while (word != 0)
    {
        uint64_t at_word = data[static_cast<size_t>(word)];
        if (at_word != 0)
            return word + 1;
        --word;
    }

    return 0;
}

mask_t::data_type mask_t::length() const
{
    auto word = data.size() - 1;
    while (word != 0)
    {
        uint64_t at_word = data[static_cast<size_t>(word)];
        if (at_word != 0)
        {
            data_type bit = 63;
            while (bit != 0)
            {
                if ((at_word & (1ull << (bit & 0x3F))) != 0ull)
                    return (word << 6) + bit;
                --bit;
            }
        }
        --word;
    }

    return 0;
}

bool mask_t::is_empty() const
{
    data_type length = data.size();
    for (data_type i = 0; i < length; i++)
    {
        if (data[static_cast<size_t>(i)] != 0ull)
            return false;
    }

    return true;
}

mask_t::data_type mask_t::next_set_bit(data_type from_index)
{
    data_type word = from_index >> 6;
    if (word >= data.size())
        return -1;

    uint64_t at_word = data[static_cast<size_t>(word)];
    if (at_word != 0)
    {
        for (data_type i = from_index & 0x3f; i < 64; i++)
        {
            if ((at_word & (1ull << (i & 0x3F))) != 0ull)
                return (word << 6) + i;
        }
    }

    for (word++; word < data.size(); word++)
    {
        if (word != 0)
        {
            at_word = data[static_cast<size_t>(word)];
            if (at_word != 0)
            {
                for (data_type i = 0; i < 64; i++)
                {
                    if ((at_word & (1ull << (i & 0x3F))) != 0ull)
                        return (word << 6) + i;
                }
            }
        }
    }

    return -1;
}

mask_t::data_type mask_t::next_clear_bit(data_type from_index) const
{
    data_type word = from_index >> 6;
    if (word >= data.size())
        return -1;

    uint64_t at_word = data[static_cast<size_t>(word)];
    for (data_type i = from_index & 0x3f; i < 64; i++)
    {
        if ((at_word & (1ull << (i & 0x3F))) == 0ull)
            return (word << 6) + i;
    }

    for (word++; word < data.size(); word++)
    {
        if (word == 0)
            return word << 6;
        at_word = data[static_cast<size_t>(word)];
        for (data_type i = 0; i < 64; i++)
        {
            if ((at_word & (1ull << (i & 0x3F))) == 0ull)
                return (word << 6) + i;
        }
    }
    return -1;
}

mask_t mask_t::operator&(const mask_t& other) const
{
    mask_t copy = *this;
    return (copy &= other);
}

mask_t mask_t::operator|(const mask_t& other) const
{
    mask_t copy = *this;
    return (copy |= other);
}

mask_t mask_t::operator^(const mask_t& other) const
{
    mask_t copy = *this;
    return (copy ^= other);
}

mask_t& mask_t::operator&=(const mask_t& other)
{
    data_type common_words = std::min(data.size(), other.data.size());
    for (data_type i = 0; common_words > i; i++)
        data[static_cast<size_t>(i)] &= other.data[static_cast<size_t>(i)];

    if (data.size() > common_words)
    {
        for (data_type i = common_words, s = data.size(); s > i; i++)
            data[static_cast<size_t>(i)] = 0ull;
    }

    return *this;
}

void mask_t::and_not(const mask_t& other)
{
    for (data_type i = 0, j = data.size(), k = other.data.size(); i < j && i < k; i++)
        data[static_cast<size_t>(i)] &= ~other.data[static_cast<size_t>(i)];
}

mask_t& mask_t::operator|=(const mask_t& other)
{
    data_type common_words = std::min(data.size(), other.data.size());
    for (data_type i = 0; common_words > i; i++)
        data[static_cast<size_t>(i)] |= other.data[static_cast<size_t>(i)];

    if (common_words < other.data.size())
    {
        check_capacity(other.data.size());
        for (data_type i = common_words, s = other.data.size(); s > i; i++)
            data[static_cast<size_t>(i)] = other.data[static_cast<size_t>(i)];
    }

    return *this;
}

mask_t& mask_t::operator^=(const mask_t& other)
{
    data_type common_words = std::min(data.size(), other.data.size());

    for (data_type i = 0; common_words > i; i++)
        data[static_cast<size_t>(i)] ^= other.data[static_cast<size_t>(i)];

    if (data.size() > common_words)
    {
        for (data_type i = other.data.size(), s = data.size(); s > i; i++)
            data[static_cast<size_t>(i)] = 0ull;
    }
    else if (common_words < other.data.size())
    {
        check_capacity(other.data.size());
        for (data_type i = common_words, s = other.data.size(); s > i; i++)
            data[static_cast<size_t>(i)] = other.data[static_cast<size_t>(i)];
    }

    return *this;
}

bool mask_t::intersects(const mask_t& other) const
{
    data_type i = std::min(data.size(), other.data.size()) - 1;
    while (i != 0)
    {
        if ((data[static_cast<size_t>(i)] & other.data[static_cast<size_t>(i)]) != 0)
            return true;
        --i;
    }

    return false;
}

bool mask_t::contains_all(const mask_t& other) const
{
    for (data_type i = data.size(); i < other.data.size(); i++)
    {
        if (other.data[static_cast<size_t>(i)] != 0)
            return false;
    }

    data_type i = std::min(data.size(), other.data.size()) - 1;
    while (i != 0)
    {
        if ((data[static_cast<size_t>(i)] & other.data[static_cast<size_t>(i)]) != other.data[static_cast<size_t>(i)])
            return false;
        --i;
    }

    return true;
}

bool mask_t::equals(const mask_t& other) const
{
    if (this == &other)
        return true;

    data_type common_words = std::min(data.size(), other.data.size());
    for (data_type i = 0; common_words > i; i++)
    {
        if (data[static_cast<size_t>(i)] != other.data[static_cast<size_t>(i)])
            return false;
    }

    if (data.size() == other.data.size())
        return true;

    return length() == other.length();
}
} // namespace eden::ecs
