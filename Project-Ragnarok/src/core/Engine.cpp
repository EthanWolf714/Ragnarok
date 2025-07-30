#include "Engine.h"
#include <GL/glew.h>
#include <SDL3/SDL.h>


Engine::Engine() {

}


Engine::~Engine() {
	Shutdown();
}




bool Engine::Initialize()
{
	m_timer = std::make_unique<Timer>();
	m_renderer = std::make_unique<Renderer>();
	if (!InitSDL()) {
		return false;
	}

	m_renderer->Initialize();

	return true;
}
//function that handles SDL initialization
bool Engine::InitSDL()
{
	bool success = true;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create Window
		gWindow = SDL_CreateWindow("Ragnarok Engine", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (gWindow == NULL)
		{
			SDL_Log("Window coult not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//create Context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				SDL_Log("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					SDL_Log("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
					success = false;

				}

				//Use VSynce
				if (!SDL_GL_SetSwapInterval(1))
				{
					SDL_Log("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

			}
		}

	}
	return success;
}



void Engine::Update()
{
	// Your original update() function content
	// Currently empty in your code
	m_timer->Update();
	
	
}

void Engine::Render()
{
	// Call the renderer's render function
	if (m_renderer)
	{
		m_renderer->Render();
	}
	else
	{
		SDL_Log("Renderer not initialized.");
	}
}


void Engine::Shutdown()
{

	// Destroy window
	if (gWindow != nullptr) {
		SDL_DestroyWindow(gWindow);
		gWindow = nullptr;
	}

	// Destroy context
	if (gContext != nullptr) {
		SDL_GL_DestroyContext(gContext);
		gContext = nullptr;
	}

	// Quit SDL
	SDL_Quit();
}