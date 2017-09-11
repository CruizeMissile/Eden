#include "Precompiled.h"

#include "LayerExtentions.h"

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
            std::vector<const char*> LayerExtentions::instance_layers;
            std::vector<const char*> LayerExtentions::instance_extentions{ VK_KHR_SURFACE_EXTENSION_NAME };
            std::vector<const char*> LayerExtentions::device_layers;
            std::vector<const char*> LayerExtentions::device_extentions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
        }
    }
}
