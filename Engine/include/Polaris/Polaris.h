#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>
#include <map>
#include <optional>
#include <set>

#include "PolarisHelpers.h"

namespace Polaris
{
    class Polaris
    {
    public:
        Polaris();
        ~Polaris();

        void Loop();
        void Cleanup();
    
    private:
        void createWindow();
        void createSurface();

        GLFWwindow* window;
        VkSurfaceKHR surface;
        VkQueue presentQueue;

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME  
        };
    private:
        VkInstance instance;
        void createInstance();

        VkDebugUtilsMessengerEXT debugMessenger;
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;

        void createLogicalDevice();
        void pickPhysicalDevice();
        int rateDeviceSuitability(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
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