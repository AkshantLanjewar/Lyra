#include "Polaris/Polaris.h"

namespace Polaris
{

    bool checkDeviceExtensionSupport(VkPhysicalDevice device, std::vector<const char*> deviceExtensions)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for(const auto& extension : availableExtensions)
            requiredExtensions.erase(extension.extensionName);
        return requiredExtensions.empty();
    }

    bool Polaris::isDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = findQueueFamilies(device);
        bool extensionsSupported = checkDeviceExtensionSupport(device, deviceExtensions);
        bool swapChainAdequate = false;

        if(extensionsSupported) {
            
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    void Polaris::pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if(deviceCount == 0)
            throw std::runtime_error("failed to find GPU with vulkan support");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        
        std::multimap<int, VkPhysicalDevice> candidates;
        for(const auto& device : devices)
        {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        if(candidates.rbegin()->first > 0)
            physicalDevice = candidates.rbegin()->second;
        if(physicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("failed to find a suitable GPU");
    }

    int Polaris::rateDeviceSuitability(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        QueueFamilyIndices indices = findQueueFamilies(device);
        bool extensionsSupported = checkDeviceExtensionSupport(device, deviceExtensions);

        int score = 0;
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            score += 1000;

        score += deviceProperties.limits.maxImageDimension2D;
        if(!deviceFeatures.geometryShader)
            return 0;
        if(!indices.isComplete() || !extensionsSupported)
            return 0;

        return score;
    }

    //Queue Families
    QueueFamilyIndices Polaris::findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;
        bool extensionsSupported = checkDeviceExtensionSupport(device, deviceExtensions);

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for(const auto& queueFamily : queueFamilies) {
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = i;

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            if(presentSupport)
                indices.presentFamily = i;
            
            if(indices.isComplete() && extensionsSupported)
                break;
            
            i++;
        }

        return indices;
    }

    void Polaris::createLogicalDevice()
    {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else
            createInfo.enabledLayerCount = 0;

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
            throw std::runtime_error("failed to create logical device!");

        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }
}