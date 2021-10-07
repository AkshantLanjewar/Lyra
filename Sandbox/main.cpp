#include <iostream>
#include <Lyra/Window.h>
#include <Polaris/Polaris.h>

int main() {
    Lyra::Window _window;
    Polaris::Polaris _renderer;
    

    _window.CreateWindow();
    _window.WindowLoop();
    _window.DestroyWindow();

    return 0;
}