#include "CL_EventHandler.hpp"

#include "gMouse.hpp"
#include "gQuit.hpp"
#include "CL_EventNames.hpp"

#include <iostream>

Mouse_Event CL_EventHandler::handleEvent(SDL_Event &e)
{
	//User requests quit
	if (e.type == SDL_QUIT)
	{
		gQuitGame = true;
		return Mouse_Event::NO_EVENT;
	} // event type -> SDL_QUIT X-Window
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		gMouse.BtnDown();
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		gMouse.BtnUp();
	}

	return Mouse_Event::NO_EVENT;
}