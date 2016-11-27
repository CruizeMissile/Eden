#pragma once

#include "Vulkan.h"
//#include "Instance.h"
//#include "PhysicalDevice.h"

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

				operator VkDevice&() { return device; }

				VkDevice device;
				VkQueue graphics_queue;
				VkQueue present_queue;
			};
		}
	}
}