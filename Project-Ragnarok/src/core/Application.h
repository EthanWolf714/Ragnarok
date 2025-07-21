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
    void Run();
    void Shutdown();
    SDL_Window* GetWindow() const { return gWindow; }

private:
    // Screen dimensions
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    SDL_Window* gWindow;
    SDL_GLContext gContext;

    std::unique_ptr<Engine> m_engine;
    std::unique_ptr<Input> m_input;

    bool InitSDL();
    bool InitGL();
    void HandleEvents();
};