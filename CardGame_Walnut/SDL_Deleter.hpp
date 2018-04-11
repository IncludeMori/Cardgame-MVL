#pragma once

#include <SDL.h>

namespace Sdl_del
{
	struct SDL_Deleter {
		void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); }
		void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
		void operator()(SDL_RWops*    ptr) { if (ptr) SDL_RWclose(ptr); }
	};
}