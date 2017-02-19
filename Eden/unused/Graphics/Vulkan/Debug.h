#pragma once

#include "Vulkan.h"

namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			class Instance;
			class Debug
			{
			public:
				Debug(Instance& instance);
				~Debug();
				static void SetupLayerExtentions();

				VkDebugReportCallbackEXT report;
				PFN_vkCreateDebugReportCallbackEXT create_report_callback_fr;
				PFN_vkDestroyDebugReportCallbackEXT destroy_report_callback_fr;

			private:
				Instance& instance;
			};
		}
	}
}