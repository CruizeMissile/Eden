
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

namespace eden::ecs
{
    template<size_t BlockSize>
    class dynamic_bitset
    {
        using size_type = size_t;
        using block_type = std::bitset<BlockSize>;
        using buffer_type = std::vector<block_type>;

        buffer_type bits_;

    public:
        dynamic_bitset() noexcept;

        // An integral value whose bits are copied to the bitset positions.
        // If the value is less then the size of the chunk then the leading
        // positions will be set to zero.
        dynamic_bitset(size_t value) noexcept;
        ~dynamic_bitset();

        dynamic_bitset(const dynamic_bitset&) = default;
        dynamic_bitset(dynamic_bitset&&) = default;

        dynamic_bitset& operator=(const dynamic_bitset&) = default;
        dynamic_bitset& operator=(dynamic_bitset&&) = default;

        // The function returns the value to the bit at position pos.
        // Note: With this operator, no range check is performed. Use test() to access the value with bitset bounds checked
        bool operator[](size_type index) const;

        // Returns the number of bits in the bitset that are set
        // For the total number of bits in the bitset (including both zeros and ones), see size().
        size_type count() const noexcept;

        // Returns the number of bits in the bitset.
        size_type size() noexcept;

        // Returns whether the bit at position pos is set (i.e., whether it is one).
        // Unlike the access operator[] this function performs a range check on pos
        // before retrieveing the bit value, throwing out_of_range if pos is
        // equal or greater than the bitset size.
        bool test(size_type index) const;

        // Returns whether any of the bits is set
        bool any() const noexcept;

        // Returns whether none of the bits is set
        bool none() const noexcept;

        // Test if all bits are set. Returns whether all of the bits in the bitset are set
        bool all() const noexcept;

        // sets one to all the bits
        dynamic_bitset& set() noexcept;

        // sets the bit in the index to the value
        dynamic_bitset& set(size_type index, bool value = true);

        // reset all the bits to zero
        dynamic_bitset& reset() noexcept;

        // reset bit at index to zero
        dynamic_bitset& reset(size_type index);

        // flip all bits
        dynamic_bitset& flip() noexcept;

        // flip bit at index
        dynamic_bitset& flip(size_type index);

        std::string to_string(char zero = '0', char one = '1');

        // dynamic_bitset operator&(const dynamic_bitset& rhs);
        // dynamic_bitset operator|(const dynamic_bitset& rhs);
        // dynamic_bitset operator^(const dynamic_bitset& rhs);

        dynamic_bitset& operator&=(const dynamic_bitset& rhs);
        dynamic_bitset& operator|=(const dynamic_bitset& rhs);
        dynamic_bitset& operator^=(const dynamic_bitset& rhs);

        bool operator==(const dynamic_bitset& rhs) const noexcept;
        bool operator!=(const dynamic_bitset& rhs) const noexcept;

    private:
        void check_capacity(size_t n);
        constexpr size_t get_highest_bit_count(size_t value);
    };

    template<size_t BlockSize>
    dynamic_bitset<BlockSize> operator&(const dynamic_bitset<BlockSize>& lhs, const dynamic_bitset<BlockSize>& rhs);

    template<size_t BlockSize>
    dynamic_bitset<BlockSize> operator|(const dynamic_bitset<BlockSize>& lhs, const dynamic_bitset<BlockSize>& rhs);

    template<size_t BlockSize>
    dynamic_bitset<BlockSize> operator^(const dynamic_bitset<BlockSize>& lhs, const dynamic_bitset<BlockSize>& rhs);

    using mask_t = dynamic_bitset<16>;

    namespace internal
    {
        template<typename Type>
        mask_t component_mask();

        template<typename Type1, typename Type2, typename... Types>
        mask_t component_mask();
    } // namespace internal
}


#include "mask.inl"
