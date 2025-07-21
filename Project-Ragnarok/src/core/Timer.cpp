#include "Timer.h"

Timer:: Timer()
	: currentTicks(0), previousTicks(0), deltaTime(0.0f) {
	currentTicks = previousTicks = SDL_GetTicks();
}

void Timer::Update() {
	previousTicks = currentTicks;
	currentTicks = SDL_GetTicks();

	//Calculate delta time in seconds
	deltaTime = (currentTicks - previousTicks) / 1000.0f;

	//cap delta time to prevent huge jumps 
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;//Max 50ms frame time
	}

	
}