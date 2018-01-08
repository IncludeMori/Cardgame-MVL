//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: handles the next event on queue
//
#pragma once

#include <SDL.h>

class Click_EventHandler
{
public:
	bool handleEvent(SDL_Event &e);
};