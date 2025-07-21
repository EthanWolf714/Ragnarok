#pragma once
#include <SDL3/SDL.h>

class Timer {
public:
    Timer();

    void Update();
    float GetDeltaTime() const { return deltaTime; }
    Uint64 GetTicks() const { return currentTicks; }

private:
    Uint64 currentTicks;
    Uint64 previousTicks;
    float deltaTime;
};