
#pragma once

#include "defines.hpp"

namespace eden::ecs
{
struct id_t
{
    id_t() = default;
    id_t(index_t index, version_t version)
        : index(index)
        , version(version)
    {
    }

    bool operator==(const id_t& other)
    {
        return index == other.index && version == other.version;
    }

    bool operator!=(const id_t& other)
    {
        return index != other.index || version != other.version;
    }

    index_t index = 0;
    version_t version = 0;
};
} // namespace eden::ecs
