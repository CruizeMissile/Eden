#pragma once

#include "../../Application/Application.h"
#include "Vulkan.h"

namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			class Instance;
			class Surface
			{

			public:
				Surface(Instance& instance, Window& window);
				~Surface();

				static void SetupLayerExtentions();

				operator VkSurfaceKHR&() { return surface; }

				VkSurfaceKHR surface;

			private:
				Instance& instance;
			};
		}
	}
}