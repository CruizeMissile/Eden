
#pragma once

#include "resource.hpp"
#include "texture_flags.hpp"

namespace eden::render
{
class texture_t : public resource_t
{
public:
    resource_type_t query_resource_type() const override
    {
        return resource_type_t::texture;
    }

protected:
    texture_t(const texture_type_t type)
        : type_(type)
    {}

private:
    texture_type_t type_;
};
} // namespace eden::render
