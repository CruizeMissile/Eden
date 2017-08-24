#pragma once

#include "../../Core/Types.h"
#include "Vulkan.h"
#include <vector>

namespace edn
{
	namespace Graphics
	{
		namespace Vk
		{
			class Instance
			{
			public:
				struct CreateInfo
				{
					String application_name;
					String engine_name;
				};

				Instance();
				~Instance();

				operator VkInstance&() { return instance; }

				VkInstance instance = nullptr;
			};
		}
	}
}