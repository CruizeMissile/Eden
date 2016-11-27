#pragma once

#include "Vulkan.h"
#include <vector>

namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			class Instance;
			class Surface;
			class PhysicalDevice
			{
			public:
				PhysicalDevice(Instance& instance, Surface& surface);

				operator VkPhysicalDevice&() { return gpu; }

				VkPhysicalDevice gpu = nullptr;
				VkPhysicalDeviceProperties properties;
				VkPhysicalDeviceMemoryProperties memory_properties;
				VkPhysicalDeviceFeatures features;

				std::vector<VkQueueFamilyProperties> queues;
				std::vector<VkExtensionProperties> extentions;
				std::vector<VkLayerProperties> layers;

			};
		}
	}
}