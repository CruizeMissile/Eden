#pragma once

#include "Vulkan.h"

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
            class Instance;
            class PhysicalDevice;
            class Surface;
            class Device
            {
            public:
                Device(Instance& instance, PhysicalDevice& gpu, Surface& surface);
                ~Device();

                operator VkDevice&() { return device; }

                VkDevice device;
                VkQueue graphics_queue;
                VkQueue present_queue;
            };
        }
    }
}
