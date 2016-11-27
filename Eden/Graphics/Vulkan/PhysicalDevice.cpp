#include "Precompiled.h"

#include "PhysicalDevice.h"
#include "Instance.h"
#include "Utility.h"
#include "LayerExtentions.h"
#include <map>
#include <set>

namespace edn 
{
	namespace Graphics 
	{
		namespace Vk
		{
			struct SwapChainSupportDetails
			{
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> presentModes;
			};

			SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR surface)
			{
				SwapChainSupportDetails details;

				vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

				u32 format_count;
				vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);
				if (format_count != 0)
				{
					details.formats.resize(format_count);
					vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
				}

				u32 present_mode_count = 0;
				vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);
				if (present_mode_count != 0)
				{
					details.presentModes.resize(present_mode_count);
					vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.presentModes.data());
				}

				return details;
			}

			u32 rate_device_suitablity(VkPhysicalDevice device, VkSurfaceKHR surface)
			{
				u32 score = 0;
				QueueFamilyIndices indices = find_queue_families(device, surface);

				if (!indices.isComplete())
					return 0;

				// Checking swapchain support
				auto swap_chain_support = query_swap_chain_support(device, surface);
				if (swap_chain_support.formats.empty() || swap_chain_support.presentModes.empty())
					return 0;

				VkPhysicalDeviceProperties properties;
				VkPhysicalDeviceFeatures features;

				vkGetPhysicalDeviceProperties(device, &properties);
				vkGetPhysicalDeviceFeatures(device, &features);

				if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
					score += 1000;

				// Max possible size of texture significantly affects performance advantage
				score += properties.limits.maxImageDimension2D;

				// Lets say that if it doesnt support geometry shaders then it will not be supported
				//if (!features.geometryShader)
				//	return 0;

				return score;
			}

			PhysicalDevice::PhysicalDevice(Instance& instance, Surface& surface)
			{
				u32 count = 0;
				vkEnumeratePhysicalDevices(instance, &count, nullptr);
				std::vector<VkPhysicalDevice> list(count);
				vkEnumeratePhysicalDevices(instance, &count, list.data());
				std::map<u32, VkPhysicalDevice> candidates;

				for (const auto& device : list)
				{
					u32 score = rate_device_suitablity(device, surface);
					candidates[score] = device;
				}

				// Checkig if the best candidate is suitable at all
				if (candidates.begin()->first == 0)
					throw std::runtime_error("Failed to find suitable gpu");
				gpu = candidates.begin()->second;
			}
		}
	}
}