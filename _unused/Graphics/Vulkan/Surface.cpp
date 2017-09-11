#include "Precompiled.h"

#include "Instance.h"
#include "LayerExtentions.h"
#include "Surface.h"

namespace edn
{
    namespace Graphics
    {
        namespace Vk
        {
            void create_surface(VkInstance& instance, VkSurfaceKHR& surface, Window& window)
            {
#if defined(EDN_WINDOWS)
                auto hwnd = window.getHwnd();
                auto hinstance = window.getHInstance();

                VkWin32SurfaceCreateInfoKHR create_info = {};
                create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                create_info.hwnd = hwnd;
                create_info.hinstance = hinstance;

                auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR");
                if (!CreateWin32SurfaceKHR || CreateWin32SurfaceKHR(instance, &create_info, nullptr, &surface) != VK_SUCCESS)
                    throw std::runtime_error("failed to create window surface!");
#endif
            }

            Surface::Surface(Instance& instance, Window& window)
                : instance(instance)
            {
                create_surface(instance, surface, window);
            }

            Surface::~Surface()
            {
                vkDestroySurfaceKHR(instance, surface, nullptr);
            }

            void Surface::SetupLayerExtentions()
            {
#if defined (EDN_WINDOWS)
                LayerExtentions::instance_extentions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif
            }

        }
    }
}
