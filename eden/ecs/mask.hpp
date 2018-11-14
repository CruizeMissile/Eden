
#pragma once

#include <iostream>
#include <string>
#include <vector>

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
