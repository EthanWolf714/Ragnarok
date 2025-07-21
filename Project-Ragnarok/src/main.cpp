#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include "core/Application.h"

int main(int argc, char* argv[]) 
{
	//create application
	Application app;

	if (!app.Initialize())
	{
		SDL_Log("Failed to initialize!\n");
		return -1;
	}

	app.Run();
	app.Shutdown();

	return 0;
}