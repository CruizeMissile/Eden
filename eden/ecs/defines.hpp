
#pragma once

#include <cstdint>

#ifndef EDEN_CACHE_LINE_SIZE
#    define EDEN_CACHE_LINE_SIZE 64
#endif

#ifndef EDEN_MAX_COMPONENTS
#    define EDEN_MAX_COMPONENTS 64
#endif

#ifndef EDEN_DEFAULT_CHUNK_SIZE
#    define EDEN_DEFAULT_CHUNK_SIZE EDEN_CACHE_LINE_SIZE
#endif

namespace eden::ecs
{
using index_t = uint32_t;
using version_t = uint8_t;

namespace internal
{
    template<typename T>
    uint32_t get_unique_type_id()
    {
        static uint32_t type = 0;
        return type++;
    }

    struct store_marker;
    struct component_marker;
    struct system_marker;
    struct entity_marker;
} // namespace internal

template<typename T>
uint32_t get_store_id()
{
    static uint32_t type = internal::get_unique_type_id<internal::store_marker>();
    return type;
}

template<typename T>
uint32_t get_component_id()
{
    static uint32_t type = internal::get_unique_type_id<internal::component_marker>();
    return type;
}

template<typename T>
uint32_t get_system_id()
{
    static uint32_t type = internal::get_unique_type_id<internal::system_marker>();
    return type;
}

template<typename T>
uint32_t get_entity_id()
{
    static uint32_t type = internal::get_unique_type_id<internal::entity_marker>();
    return type;
}
} // namespace eden::ecs
