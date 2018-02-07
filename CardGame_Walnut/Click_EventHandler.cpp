#include "Click_EventHandler.hpp"

#include "gMouse.hpp"
#include "gQuit.hpp"

bool Click_EventHandler::handleEvent(SDL_Event &e)
{
	bool ok = true;

	if (gMouse.isPressed())
		gMouse.BtnUp();

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
		//gMouse.BtnDown();
	}

	

	return ok;
}
