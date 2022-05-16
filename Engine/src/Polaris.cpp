#include "Polaris/Polaris.h"

namespace Polaris 
{
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if(func != nullptr)
            func(instance, debugMessenger, pAllocator);
    }

    Polaris::Polaris()
    {
        createWindow();

        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
    }

    Polaris::~Polaris()
    {

    }

    void Polaris::Cleanup()
    {
        vkDestroyDevice(device, nullptr);
        if(enableValidationLayers)
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
    }
}