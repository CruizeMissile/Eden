
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

        dynamic_bitset operator&(const dynamic_bitset& rhs);
        dynamic_bitset operator|(const dynamic_bitset& rhs);
        dynamic_bitset operator^(const dynamic_bitset& rhs);

        dynamic_bitset& operator&=(const dynamic_bitset& rhs);
        dynamic_bitset& operator|=(const dynamic_bitset& rhs);
        dynamic_bitset& operator^=(const dynamic_bitset& rhs);

        bool operator==(const dynamic_bitset& rhs) const noexcept;
        bool operator!=(const dynamic_bitset& rhs) const noexcept;

    private:
        void check_capacity(size_t n);
        constexpr size_t get_highest_bit_count(size_t value);
    };
}

namespace eden::ecs
{
class mask_t
{
private:
    using data_type = uint64_t;
    using buffer_type = std::vector<data_type>;
    buffer_type data;

public:
    mask_t();
    ~mask_t();
    mask_t(const mask_t&);
    mask_t(mask_t&& other);
    explicit mask_t(data_type set_bit);
    mask_t& operator=(const mask_t&);
    mask_t& operator=(mask_t&&);

    bool get(data_type index) const;
    bool get_and_clear(data_type index);
    bool get_and_set(data_type index);

    void set(data_type index);
    void flip(data_type index);

    // return All uint64_t's as string, comma separated
    std::string to_string() const;

    buffer_type& get_data();

private:
    void check_capacity(data_type len);
    bool equals(const mask_t& other) const;

public:
    void clear(data_type index);
    void clear();

    data_type num_bits() const;
    data_type used_words() const;

    // Returns the "logical size" of the bitset. This means the index of the
    // highest set of bits in the bitset plus one.
    // Returns zero if the bitset is contains no set bits
    data_type length() const;

    // Returns true if the bitset has no bits set to true
    bool is_empty() const;

    // Return the next set bit starting from the index provided.
    data_type next_set_bit(data_type from_index);
    // Return the next clear bit starting from the index provided.
    data_type next_clear_bit(data_type from_index) const;

    // Clears all of the bits that match the set bits in the other instance
    void and_not(const mask_t& other);
    mask_t operator&(const mask_t& other) const;
    mask_t operator|(const mask_t& other) const;
    mask_t operator^(const mask_t& other) const;

    mask_t& operator&=(const mask_t& other);
    mask_t& operator|=(const mask_t& other);
    mask_t& operator^=(const mask_t& other);

    // Returns true if any bits are set in both instances
    bool intersects(const mask_t& other) const;

    // Returns true if this instance is a super set of the other instance.
    // This means that it has all bits set to true that are also true
    // in the other instance.
    bool contains_all(const mask_t& other) const;

    bool operator==(const mask_t& other) const { return equals(other); }
    bool operator!=(const mask_t& other) const { return !equals(other); }

    std::ostream& operator<<(std::ostream& os);
};

namespace internal
{
    template<typename Type>
    mask_t component_mask();

    template<typename Type1, typename Type2, typename... Types>
    mask_t component_mask();
} // namespace internal
} // namespace eden::ecs

#include "mask.inl"
