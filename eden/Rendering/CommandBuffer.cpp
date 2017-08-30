#include "CommandBuffer.h"


namespace edn::rendering
{
    Command::Command(u16 id, u16 size)
    : id(id)
    , size(size)
    {
    }
    
    CommandBuffer::CommandBuffer(Type type)
    : type(type)
    , command_count(0u)
    , enabled(true)
    {
    }
    
    u32 CommandBuffer::push_command(const Command& command)
    {
        // Push comand to buffer
        const u32 pos = command_buffer.push_data(&command, command.size);
        
        // Increment command count
        command_count++;
        
        return pos;
    }
    
    void CommandBuffer::clear()
    {
        command_buffer.reset();
        command_count = 0u;
        enabled = true;
    }
    
    u32 CommandBuffer::get_command_count() const
    {
        return command_count;
    }
    
    const void* CommandBuffer::get_data() const
    {
        return command_buffer.get_data();
    }
    
    CommandBuffer::Type CommandBuffer::get_type() const
    {
        return type;
    }

    bool CommandBuffer::is_enabled() const
    {
        return enabled;
    }

    void CommandBuffer::set_enabled(bool value)
    {
        enabled = value;
    }
}
