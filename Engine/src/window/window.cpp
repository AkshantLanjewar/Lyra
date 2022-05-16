#include "Polaris/Polaris.h"

namespace Polaris
{
    void Polaris::createWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(1280, 720, "Polaris", nullptr, nullptr);
    }

    void Polaris::createSurface()
    {
        if(glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
            throw std::runtime_error("Failed to create window surface");
    }

    void Polaris::Loop()
    {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }
}