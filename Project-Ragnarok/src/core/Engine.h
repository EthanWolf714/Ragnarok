#pragma once
#include <GL/glew.h>
#include "Timer.h"
#include <memory>

class Engine {
public:
    Engine();
    ~Engine();

    bool Initialize();
    void Update();
    void Render();
    void Shutdown();



private:
    std::unique_ptr<Timer> m_timer;
};