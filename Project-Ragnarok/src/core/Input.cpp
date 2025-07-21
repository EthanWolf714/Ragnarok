#include "Input.h"
#include "Engine.h"
#include <SDL3/SDL.h>

Input::Input() : m_engine(nullptr) {
}

Input::~Input() {
}

void Input::HandleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		
	}
}

void Input::HandleKeys(unsigned char key)
{

}