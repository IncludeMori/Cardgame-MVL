//
// @Author: Moritz Volkenandt (2017-)
// 
// purpose:initialize SDL
//
#pragma once

#include <string>

class SDL_init
{
public:
	bool SDLinit(const int SCREEN_WIDTH, const int SCREEN_HEIGHT,
		const std::string WINDOW_NAME);
	void SDLclose(); 
};