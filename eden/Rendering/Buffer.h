#pragma once

#include <memory>

namespace edn::rendering
{
    class Buffer
    {
    public:
        struct View
        {
          Buffer& buffer;
          const u32 offset;
          const u32 size;

          void* get_data(u32 offset = 0u);
          const void* get_data(u32 offset = 0u) const;
        };
        
        Buffer();
        Buffer(u32 size);
        Buffer(const Buffer&) = delete;
        ~Buffer();
        
        View allocate_range(u32 range_size);
        u32 push_data(const void* data, u32 data_size);
        
        u32 get_size() const;
        u32 get_offset() const;
        void* get_data(u32 offset = 0u);
        const void* get_data(u32 offset = 0u) const;
        
        void reset();
        
    private:
        void alloc(u32 size);
        void reserve_space(u32 size);
        
        void* data;
        u32 offset;
        u32 position;
        u32 size;
    };
}
