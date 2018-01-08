//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: handles the next event on queue-> collection
//
#pragma once

#include <SDL.h>
#include "CL_EventNames.hpp"

class CL_EventHandler
{
public:
	Mouse_Event handleEvent(SDL_Event &e);
private:
};
