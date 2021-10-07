#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>
#include <map>
#include <optional>

namespace Polaris
{

    //structures
    struct QueueFamilyIndices 
    {
        std::optional<uint32_t> graphicsFamily;
    };

    class Polaris
    {
    public:
        Polaris();
        ~Polaris();

        void Cleanup();

    private:
        VkInstance instance;
        void createInstance();

        VkDebugUtilsMessengerEXT debugMessenger;
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        void pickPhysicalDevice();
        int rateDeviceSuitability(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        #ifdef NDEBUG
            const bool enableValidationLayers = false;
        #else
            const bool enableValidationLayers = true;
        #endif
    };
}