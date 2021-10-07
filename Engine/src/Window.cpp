#include "../include/Lyra/Window.h";

namespace Lyra 
{
    Window::Window() 
    {

    }

    Window::~Window()
    {

    }

    void Window::CreateWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        this->window = glfwCreateWindow(800, 600, "Lyra", nullptr, nullptr);
    }

    void Window::WindowLoop()
    {
        while(!glfwWindowShouldClose(this->window)) {
            glfwPollEvents();
        }
    }

    void Window::DestroyWindow()
    {
        renderingEngine->Cleanup();
        
        glfwDestroyWindow(this->window);
        glfwTerminate();    
    }

    void Window::AttachRenderer(Polaris::Polaris* renderingEngine)
    {
        this->renderingEngine = renderingEngine;
    }
}