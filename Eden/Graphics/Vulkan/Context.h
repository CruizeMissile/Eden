#pragma once

#include "Vulkan.h"
#include "Instance.h"
#include "Surface.h"
#include "Debug.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "../../Application/Application.h"


namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			class Context
			{
			public:
				Context(Window& window)
					: instance()
					, debug(instance)
					, surface(instance, window)
					, gpu(instance, surface)
					, device(instance, gpu, surface)
				{
				}

				static void SetupVk()
				{
					Surface::SetupLayerExtentions();
					Debug::SetupLayerExtentions();
				}

			//protected:
				Instance instance;
				Surface surface;
				PhysicalDevice gpu;
				Device device;
				Debug debug;
			};
		}
	}
}
