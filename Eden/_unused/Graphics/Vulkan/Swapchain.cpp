#include "Precompiled.h"

#include "Swapchain.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "Utility.h"
#include "Surface.h"

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

			SwapChainSupportDetails query_swapchain_support(PhysicalDevice& gpu, Surface& surface)
			{
				SwapChainSupportDetails details;
				vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, surface, &details.capabilities);

				u32 count = 0;
				vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &count, nullptr);
				if (count > 0)
				{
					details.formats.resize(count);
					vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &count, details.formats.data());
				}

				count = 0;
				vkGetPhysicalDeviceSurfacePresentModesKHR(gpu, surface, &count, nullptr);
				if (count > 0)
				{
					details.presentModes.resize(count);
					vkGetPhysicalDeviceSurfacePresentModesKHR(gpu, surface, &count, nullptr);
				}
				return details;
			}

			VkSurfaceFormatKHR choose_swap_chain_surface_format(const std::vector<VkSurfaceFormatKHR>& avalible_formats)
			{
				if (avalible_formats.size() == 1 && avalible_formats[0].format == VK_FORMAT_UNDEFINED)
					return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

				for (const auto& format : avalible_formats)
				{
					if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
						return format;
				}
				return avalible_formats[0];
			}

			VkPresentModeKHR choose_swap_chain_present_mode(const std::vector<VkPresentModeKHR>& avalible_modes)
			{
				for (const auto& present_mode : avalible_modes)
				{
					if (present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
						return present_mode;
				}

				return VK_PRESENT_MODE_FIFO_KHR;
			}

			VkExtent2D choose_swap_chain_extent(const VkSurfaceCapabilitiesKHR& capabilities, u32 width, u32 height)
			{
				if (capabilities.currentExtent.width != std::numeric_limits<u32>::max())
					return capabilities.currentExtent;

				VkExtent2D actual_extent = { width, height };
				actual_extent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actual_extent.width));
				actual_extent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actual_extent.height));
				return actual_extent;
			}

			Swapchain::Swapchain(PhysicalDevice& gpu, Device& device, Surface& surface, Window& window)
				: device(device)
			{
				auto support = query_swapchain_support(gpu, surface);
				auto surface_format = choose_swap_chain_surface_format(support.formats);
				auto present_mode = choose_swap_chain_present_mode(support.presentModes);
				extent = choose_swap_chain_extent(support.capabilities, window.getWidth(), window.getHeight());

				u32 image_count = support.capabilities.minImageCount + 1;
				if (support.capabilities.maxImageCount > 0 && image_count > support.capabilities.maxImageCount)
					image_count = support.capabilities.maxImageCount;

				VkSwapchainCreateInfoKHR ci = {};
				ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				ci.surface = surface;
				ci.minImageCount = image_count;
				ci.imageFormat = surface_format.format;
				ci.imageColorSpace = surface_format.colorSpace;
				ci.imageExtent = extent;
				ci.imageArrayLayers = 1;
				ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

				auto indices = find_queue_families(gpu, surface);
				u32 queue_families[] = { (u32)indices.graphicsFamily, (u32)indices.presentFamily };

				if (indices.graphicsFamily != indices.presentFamily)
				{
					ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
					ci.queueFamilyIndexCount = 2;
					ci.pQueueFamilyIndices = queue_families;
				}
				else
				{
					ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
					ci.queueFamilyIndexCount = 0;
					ci.pQueueFamilyIndices = nullptr;
				}

				ci.preTransform = support.capabilities.currentTransform;
				ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				ci.presentMode = present_mode;
				ci.clipped = VK_TRUE;
				ci.oldSwapchain = VK_NULL_HANDLE;

				VKErrorCheck(vkCreateSwapchainKHR(device, &ci, nullptr, &swapchain));

				vkGetSwapchainImagesKHR(device, swapchain, &image_count, nullptr);
				images.resize(image_count);
				vkGetSwapchainImagesKHR(device, swapchain, &image_count, images.data());
				format = surface_format.format;
				}

			Swapchain::~Swapchain()
			{
				vkDestroySwapchainKHR(device, swapchain, nullptr);
			}
		}
	}
}