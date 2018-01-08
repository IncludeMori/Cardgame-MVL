#pragma once

#include <SDL.h>
#include "Camera.hpp"

class EventHandler
{
public:
	bool handleEvent(SDL_Event &e);
};