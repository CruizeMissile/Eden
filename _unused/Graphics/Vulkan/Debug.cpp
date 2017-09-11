#include "Precompiled.h"

#include "Debug.h"
#include "Instance.h"
#include "LayerExtentions.h"

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
            VkDebugReportCallbackCreateInfoEXT debug_callback_create_info;

            static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
                VkDebugReportFlagsEXT       flags,
                VkDebugReportObjectTypeEXT  obj_type,
                uint64_t                    src_obj,
                size_t                      location,
                int32_t                     msg_code,
                const char *                layer_prefix,
                const char *                msg,
                void *                      user_data
            )
            {
                std::ostringstream stream;
                stream << "[VK]: ";
                if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
                    stream << "[Info]: ";
                if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
                    stream << "[Warning]: ";
                if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
                    stream << "[Preformance]: ";
                if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
                    stream << "[Error]: ";
                if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
                    stream << "[Debug]: ";
                stream << "@[" << layer_prefix << "]: " << msg << std::endl;
                std::cout << stream.str();

#if defined(EDN_WINDOWS)
                if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
                    MessageBoxA(0, stream.str().c_str(), "Vulkan Error!", 0);
#endif
                return false;
            }

            Debug::Debug(Instance& instance)
                : instance(instance)
            {
#if defined(EDN_DEBUG)
                create_report_callback_fr = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
                destroy_report_callback_fr = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
                debug_callback_create_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
                debug_callback_create_info.pfnCallback = debug_callback;
                create_report_callback_fr(instance, &debug_callback_create_info, nullptr, &report);
#endif
            }

            Debug::~Debug()
            {
#if defined(EDN_DEBUG)
                destroy_report_callback_fr(instance, report, nullptr);
                report = VK_NULL_HANDLE;
#endif
            }

            void Debug::SetupLayerExtentions()
            {
#if defined(EDN_DEBUG)
                LayerExtentions::instance_layers.push_back("VK_LAYER_LUNARG_standard_validation");
                LayerExtentions::instance_extentions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
#endif
            }
        }
    }
}
