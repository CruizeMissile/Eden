#include "Precompiled.h"

#include "LayerExtentions.h"
#include "Utility.h"
#include <set>

namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			bool check_device_extention_support(VkPhysicalDevice device)
			{
				auto& device_extention = LayerExtentions::device_extentions;
				u32 extention_count;
				vkEnumerateDeviceExtensionProperties(device, nullptr, &extention_count, nullptr);

				std::vector<VkExtensionProperties> avalible_extentions(extention_count);
				vkEnumerateDeviceExtensionProperties(device, nullptr, &extention_count, avalible_extentions.data());

				std::set<std::string> required_extentions(device_extention.begin(), device_extention.end());

				for (const auto& extention : avalible_extentions)
					required_extentions.erase(extention.extensionName);
				return required_extentions.empty();
			}

			QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface)
			{
				QueueFamilyIndices qindices;
				u32 count = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
				std::vector<VkQueueFamilyProperties> queues(count);
				vkGetPhysicalDeviceQueueFamilyProperties(device, &count, queues.data());

				u32 i = 0;
				for (const auto& family : queues)
				{
					if (family.queueCount > 0 && family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
						qindices.graphicsFamily = i;

					VkBool32 present_support = false;
					vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);
					if (family.queueCount > 0 && present_support)
						qindices.presentFamily = i;

					auto extention_support = check_device_extention_support(device);
					if (qindices.isComplete() && extention_support)
						break;
					++i;
				}
				return qindices;
			}
		}
	}
}
