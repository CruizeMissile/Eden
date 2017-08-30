#pragma once
#include "Core/Types.h"
#include "Buffer.h"
#include <memory>

namespace edn::rendering
{
    struct Command
    {
        const u16 id;
        const u16 size;
        Command(u16 id, u16 size);
    };
    
    class CommandBuffer
    {
    public:
        enum class Type : u32
        {
          Render,
          Transfer
        };
        
        CommandBuffer(Type type);
        virtual ~CommandBuffer() = default;
        
        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer& operator=(const CommandBuffer&) = delete;
        
        void clear();
        
        const void* get_data() const;
        
        Type get_type() const;
        u32 get_command_count() const;
        
        bool is_enabled() const;
        void set_enabled(bool enabled);
        
    protected:
        u32 push_command(const Command& command);
        
        Buffer command_buffer;
        Type type;
        u32 command_count;
        bool enabled;
    };
    
    using CommandBufferPtr = std::unique_ptr<CommandBuffer>;
}
