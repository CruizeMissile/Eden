#pragma once

#include "Vulkan.h"
#include <vector>

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
            class LayerExtentions
            {
            public:
                static std::vector<const char*> instance_layers;
                static std::vector<const char*> instance_extentions;
                static std::vector<const char*> device_layers;
                static std::vector<const char*> device_extentions;
            };
        }
    }
}
