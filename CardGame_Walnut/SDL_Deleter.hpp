#pragma once

#include <SDL.h>
#include <iostream>

namespace sdl2_Deleter
{
	struct SDL_Deleter {
		void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); std::cout << "sdl_texture destroyed" << std::endl; }
		void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
		void operator()(SDL_RWops*    ptr) { if (ptr) SDL_RWclose(ptr); }
	};
}