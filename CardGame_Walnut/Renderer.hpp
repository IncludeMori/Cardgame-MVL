#pragma once

#include <SDL.h>
#include <memory>

#include "SDL_Deleter.hpp"

namespace sdl2_Renderer
{
	extern std::unique_ptr<SDL_Renderer, sdl2_Deleter::SDL_Deleter> Renderer;
}
namespace sdl2_Window
{
	extern std::unique_ptr<SDL_Window, sdl2_Deleter::SDL_Deleter> Window;
}