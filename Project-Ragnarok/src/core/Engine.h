#pragma once  
#include <GL/glew.h>  
#include "Timer.h"  
#include <memory>  
#include <SDL3/SDL.h>   
#include <SDL3/SDL_opengl.h>  
#include <GL/glu.h>  
#include "../graphics/Renderer.h"  

class Engine {  
public:  
    Engine();  
    ~Engine();  

    bool Initialize();  
    bool InitSDL();   
    void Update();  
    void Render();  
    void Shutdown();  
    SDL_Window* GetWindow() const { return gWindow; }  
    // Screen dimensions  
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
      

private:  
   
    // Window and context  
    SDL_Window* gWindow;  
    SDL_GLContext gContext;  
    std::unique_ptr<Timer> m_timer;  
    std::unique_ptr<Renderer> m_renderer;  
};