#pragma once

#include "../../Core/Platform.h"

#if defined(EDN_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR 1
#elif defined(EDN_LINUX)
#define VK_USE_PLATFORM_XCB_KHR 1
#else
#error Platform not supported by Eden
#endif

#if defined(EDN_DEBUG)
#include "../../Core/Debug.h"
#endif

#include "vulkan/vulkan.h"

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
#if defined(EDN_DEBUG)
            static void VKErrorCheck(VkResult result)
            {
                // if the result is VK_SUCCESS
                if (result == VK_SUCCESS)
                    return;

                // If not then ouput and assert the error
                std::string error_str;

                switch (result)
                {
                case VK_NOT_READY:
                    error_str = "VK_NOT_READY";
                    break;
                case VK_TIMEOUT:
                    error_str = "VK_TIMEOUT";
                    break;
                case VK_EVENT_SET:
                    error_str = "VK_EVENT_SET";
                    break;
                case VK_EVENT_RESET:
                    error_str = "VK_EVENT_RESET";
                    break;
                case VK_INCOMPLETE:
                    error_str = "VK_INCOMPLETE";
                    break;
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    error_str = "VK_ERROR_OUT_OF_HOST_MEMORY";
                    break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    error_str = "VK_ERROR_OUT_OF_DEVICE_MEMORY";
                    break;
                case VK_ERROR_INITIALIZATION_FAILED:
                    error_str = "VK_ERROR_INITIALIZATION_FAILED";
                    break;
                case VK_ERROR_DEVICE_LOST:
                    error_str = "VK_ERROR_DEVICE_LOST";
                    break;
                case VK_ERROR_MEMORY_MAP_FAILED:
                    error_str = "VK_ERROR_MEMORY_MAP_FAILED";
                    break;
                case VK_ERROR_LAYER_NOT_PRESENT:
                    error_str = "VK_ERROR_LAYER_NOT_PRESENT";
                    break;
                case VK_ERROR_EXTENSION_NOT_PRESENT:
                    error_str = "VK_ERROR_EXTENSION_NOT_PRESENT";
                    break;
                case VK_ERROR_FEATURE_NOT_PRESENT:
                    error_str = "VK_ERROR_FEATURE_NOT_PRESENT";
                    break;
                case VK_ERROR_INCOMPATIBLE_DRIVER:
                    error_str = "VK_ERROR_INCOMPATIBLE_DRIVER";
                    break;
                case VK_ERROR_TOO_MANY_OBJECTS:
                    error_str = "VK_ERROR_TOO_MANY_OBJECTS";
                    break;
                case VK_ERROR_FORMAT_NOT_SUPPORTED:
                    error_str = "VK_ERROR_FORMAT_NOT_SUPPORTED";
                    break;
                case VK_ERROR_SURFACE_LOST_KHR:
                    error_str = "VK_ERROR_SURFACE_LOST_KHR";
                    break;
                case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                    error_str = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
                    break;
                case VK_SUBOPTIMAL_KHR:
                    error_str = "VK_SUBOPTIMAL_KHR";
                    break;
                case VK_ERROR_OUT_OF_DATE_KHR:
                    error_str = "VK_ERROR_OUT_OF_DATE_KHR";
                    break;
                case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                    error_str = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
                    break;
                case VK_ERROR_VALIDATION_FAILED_EXT:
                    error_str = "VK_ERROR_VALIDATION_FAILED_EXT";
                    break;
                case VK_ERROR_INVALID_SHADER_NV:
                    error_str = "VK_ERROR_INVALID_SHADER_NV";
                    break;
                default: break;
                }

                std::string message = "Vulkan runtime error: " + error_str;
                ASSERT(false, message.c_str());
            }
#else
            static void VKErrorCheck(VkResult result) {}
#endif
        }
    }
}
