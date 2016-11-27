#include "Precompiled.h"

#include "Instance.h"
#include "LayerExtentions.h"
#include "Vulkan.h"

namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			Instance::Instance()
			{
				VkApplicationInfo app_info = {};
				app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				app_info.apiVersion = VK_MAKE_VERSION(1, 0, 2);
				app_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
				app_info.pApplicationName = "Eden Engine";
				app_info.pEngineName = "Eden Engine";
				app_info.pNext = 0;

				VkInstanceCreateInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				info.pApplicationInfo = &app_info;
				info.enabledLayerCount= static_cast<u32>(LayerExtentions::instance_layers.size());
				info.ppEnabledLayerNames = LayerExtentions::instance_layers.data();
				info.enabledExtensionCount = static_cast<u32>(LayerExtentions::instance_extentions.size());
				info.ppEnabledExtensionNames = LayerExtentions::instance_extentions.data();
				info.flags = 0;
				VKErrorCheck(vkCreateInstance(&info, nullptr, &instance));
			}
		}
	}
}