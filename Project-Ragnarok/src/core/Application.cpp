#include "Application.h"
#include "Engine.h"
#include "Input.h"
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <memory>

Application::Application() : gWindow(nullptr), gContext(nullptr) {
}

Application::~Application() {
    Shutdown();
}

bool Application::Initialize() {
    if (!InitSDL()) {
        return false;
    }

    if (!InitGL())
    {
        return false;
    }

    m_engine = std::make_unique<Engine>();
     m_input = std::make_unique<Input>();

	m_input->SetEngine(m_engine.get());

    if (!m_engine->Initialize())
    {
        return false;
    }

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
		SDL_GL_SwapWindow(gWindow);
	}
}

void Application::Shutdown()
{
    // Reset engine and input
    m_engine.reset();
    m_input.reset();

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


bool Application::InitSDL()
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

bool Application::InitGL()
{
	//set clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLenum error = glGetError();

	if (error != glGetError())
	{
		SDL_Log("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}

	return true;
}

