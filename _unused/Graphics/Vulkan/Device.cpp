#include "Precompiled.h"

#include "Device.h"
#include "Instance.h"
#include "LayerExtentions.h"
#include "PhysicalDevice.h"
#include "Surface.h"
#include "Utility.h"
#include <set>

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
            Device::Device(Instance& instance, PhysicalDevice& gpu, Surface& surface)
            {
                auto& device_extention = LayerExtentions::device_extentions;
                QueueFamilyIndices indices = find_queue_families(gpu, surface.surface);
                std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
                std::set<int> unique_queue_families = { indices.graphicsFamily, indices.presentFamily };

                float queue_priority = 1.0f;
                for (auto queue_family : unique_queue_families)
                {
                    VkDeviceQueueCreateInfo queue_create_info = {};
                    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                    queue_create_info.queueFamilyIndex = queue_family;
                    queue_create_info.queueCount = 1;
                    queue_create_info.pQueuePriorities = &queue_priority;
                    queue_create_infos.push_back(queue_create_info);
                }

                VkPhysicalDeviceFeatures device_features = {};
                VkDeviceCreateInfo create_info = {};
                create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                create_info.pQueueCreateInfos = queue_create_infos.data();
                create_info.queueCreateInfoCount = static_cast<u32>(queue_create_infos.size());
                create_info.pEnabledFeatures = &device_features;

                create_info.enabledExtensionCount = static_cast<u32>(device_extention.size());
                create_info.ppEnabledExtensionNames = device_extention.data();

                // DEBUG HERE
                create_info.enabledLayerCount = 0;

                VKErrorCheck(vkCreateDevice(gpu, &create_info, nullptr, &device));
                vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphics_queue);
                vkGetDeviceQueue(device, indices.presentFamily, 0, &present_queue);
            }

            Device::~Device()
            {
                vkDestroyDevice(device, nullptr);
            }
        }
    }
}
