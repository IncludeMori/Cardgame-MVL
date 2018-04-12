//
// @Author: Moritz Volkenandt (2017-)
// 
// purpose:initialize SDL
//
#pragma once

#include <string>

namespace sdl2_Init
{
	bool startSDL(const int screen_width, const int screen_height,
		const std::string &window_name);
	void closeSDL(); 
};