#include "Precompiled.h"
#include "Buffer.h"

namespace edn::rendering
{
    void* Buffer::View::get_data(u32 offset)
    {
        return buffer.get_data(this->offset + offset);
    }

    const void* Buffer::View::get_data(u32 offset) const
    {
        return buffer.get_data(this->offset + offset);
    }

    Buffer::Buffer()
        : data(nullptr)
        , offset(0u)
        , position(0u)
        , size(0u)
    {
    }

    Buffer::Buffer(u32 size)
        : data(nullptr)
        , offset(0u)
        , position(0u)
        , size(size)
    {
        alloc(size);
    }

    Buffer::~Buffer()
    {
        if (data)
            free(data);
    }

    Buffer::View Buffer::allocate_range(u32 range_size)
    {
        // Align the buffer to 256.
        // Note that noe every GPU requires the buffer offset
        // to be a multiple of 256.
        u32 shift = ((position + 0xFFu) & ~(0xFFu)) - position;

        // Make sure that we have enough space
        reserve_space(shift + range_size);  

        position += shift;

        // Save current offset
        offset = position;

        // Move data pointer forward
        position += range_size;

        return { *this, offset, range_size };
    }

    u32 Buffer::push_data(const void* data, u32 dataSize)
    {
        // Make sure there is enough space
        reserve_space(dataSize);

        // Copy data in buffer
        memcpy(static_cast<u8*>(this->data) + position, data, dataSize);

        // Save current offset
        offset = position;

        // Move data pointer forward
        position += dataSize;

        // Return data offset :
        return offset;
    }

    void Buffer::alloc(u32 size)
    {
        if (data)
            data = realloc(data, size);
        else
            data = malloc(size);

        ASSERT(data != nullptr, "Allocation failed for size : %u", size);

        this->size = size;
    }

    void Buffer::reserve_space(u32 size)
    {
        const u32 required_space = position + size;
        if (this->size < required_space)
            // Reallocating 1.5x the current size
            alloc(this->size + (this->size >> 1) + size);
    }

    void Buffer::reset()
    {
        position = 0u;
    }

    u32 Buffer::get_size() const
    {
        return size;
    }

    void* Buffer::get_data(u32 offset)
    {
        return static_cast<u8*>(data) + offset;
    }

    const void* Buffer::get_data(u32 offset) const
    {
        return static_cast<u8*>(data) + offset;
    }

    u32 Buffer::get_offset() const
    {
        return offset;
    }
}