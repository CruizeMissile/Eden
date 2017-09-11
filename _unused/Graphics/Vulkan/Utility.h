#pragma once

#include "Vulkan.h"

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
            struct QueueFamilyIndices
            {
                s32 graphicsFamily = -1;
                s32 presentFamily = -1;
                bool isComplete() { return graphicsFamily >= 0 && presentFamily >= 0; }
            };

            bool check_device_extention_support(VkPhysicalDevice device);
            QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface);
        }
    }
}
