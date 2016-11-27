#pragma once

#include "../../Application/Application.h"
#include "Vulkan.h"
#include <vector>

namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			class Device;
			class PhysicalDevice;
			class Surface;
			class Swapchain
			{
			public:
				Swapchain(PhysicalDevice& gpu, Device& device, Surface& surface, Window& window);
				~Swapchain();

				VkSwapchainKHR swapchain;
				VkFormat format;
				VkExtent2D extent;
				std::vector<VkImage> images;

			private:
				Device& device;
			};
		}
	}
}