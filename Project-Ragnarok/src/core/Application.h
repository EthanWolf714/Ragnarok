#pragma once
#include <SDL3/SDL.h>
#include <memory>

class Engine;
class Input;

class Application {
public:
    Application();
    ~Application();
    bool Initialize();
    void Shutdown();
    void Run();
    

private:
    

    std::unique_ptr<Engine> m_engine;
    std::unique_ptr<Input> m_input;

    
    void HandleEvents();
};