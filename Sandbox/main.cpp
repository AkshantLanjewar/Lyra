#include <iostream>
#include <Lyra/Window.h>
#include <Polaris/Polaris.h>

int main() {
    Polaris::Polaris engine;
    
    engine.Loop();
    engine.Cleanup();
    
    return 0;
}