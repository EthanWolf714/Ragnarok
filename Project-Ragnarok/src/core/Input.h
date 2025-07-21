#pragma once
#include <SDL3/SDL.h>

class Engine;

class Input {
public:
    Input();
    ~Input();

    void HandleEvent(const SDL_Event& event);
    void SetEngine(Engine* engine) { m_engine = engine; }

private:
    Engine* m_engine;

    void HandleKeys(unsigned char key);
};
