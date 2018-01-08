#include "Click_EventHandler.hpp"

#include "gMouse.hpp"
#include "gQuit.hpp"

bool Click_EventHandler::handleEvent(SDL_Event &e)
{
	bool ok = true;

	//User requests quit
	if (e.type == SDL_QUIT)
	{
		gQuitGame = true;
	} // event type -> SDL_QUIT X-Window
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		gMouse.BtnDown();
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		gMouse.BtnUp();
	}

	return ok;
}
