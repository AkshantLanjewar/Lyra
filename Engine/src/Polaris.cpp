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
        createInstance();
        setupDebugMessenger();
        pickPhysicalDevice();
    }

    Polaris::~Polaris()
    {

    }

    void Polaris::Cleanup()
    {
        if(enableValidationLayers)
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        vkDestroyInstance(instance, nullptr);
    }
}