#include "Application.h"
#include "Engine.h"
#include "Input.h"
#include <memory>

Application::Application() {
}

Application::~Application() {
   
}

bool Application::Initialize() {
	m_engine = std::make_unique<Engine>();
	m_engine->Initialize();
	m_input = std::make_unique<Input>();

	m_input->SetEngine(m_engine.get());
	return true;

}
 
void Application::HandleEvents()
{
	
}

void Application::Run()
{
	bool quit = false;
	SDL_Event e;

	// While application is running
	while (!quit)
	{
		// Handle events 
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}

			// Pass event to input handler
			m_input->HandleEvent(e);
		}

		// Update game logic
		m_engine->Update();

		// Render
		m_engine->Render();

		// Update screen
		SDL_GL_SwapWindow(m_engine->GetWindow());
	}
}

void Application::Shutdown() {
	m_engine.reset();
	m_input.reset();
}






