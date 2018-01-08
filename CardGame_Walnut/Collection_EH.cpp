#include "Collection_EH.hpp"

#include "gQuit.hpp"
#include "gMouse.hpp"
#include "Camera.hpp"

bool EventHandler::handleEvent(SDL_Event &e)
{
	bool ok = true;

	//User requests quit
	if (e.type == SDL_QUIT)
	{
		gQuitGame = true;
	} // event type -> SDL_QUIT X-Window
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		//if (e.button.clicks == 2)
		//{
			gMouse.BtnDown();
		//}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		gMouse.BtnUp();
	}
	


	return ok;



}