#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../Polaris/Polaris.h"

namespace Lyra
{
    class Window
    {
    public:
        Window();
        ~Window();

        void CreateWindow();
        void WindowLoop();
        void DestroyWindow();

        void AttachRenderer(Polaris::Polaris* renderingEngine);
    private:
        GLFWwindow* window = nullptr;
        Polaris::Polaris* renderingEngine = nullptr;
    };
}