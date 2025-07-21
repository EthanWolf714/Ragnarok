#include "Engine.h"
#include <GL/glew.h>

Engine::Engine() {

}


Engine::~Engine() {
	Shutdown();
}




bool Engine::Initialize()
{
	m_timer = std::make_unique<Timer>();
	// Any engine-specific initialization would go here
	return true;
}

void Engine::Update()
{
	// Your original update() function content
	// Currently empty in your code
	m_timer->Update();
}

void Engine::Render()
{
	// Your original render() function content
	// Clear color buffer to black
	glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::Shutdown()
{
	// Clean up any engine resources
}