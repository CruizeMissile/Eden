#pragma once

#include "render_object.hpp"
#include "resource_flags.hpp"

namespace eden::render
{
struct resource_t : public render_object_t
{
    virtual resource_type_t query_resource_type() const = 0;
};
} // namespace eden::render
