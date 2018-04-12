#include "Renderer.hpp"

namespace sdl2_Renderer
{
	std::unique_ptr<SDL_Renderer, sdl2_Deleter::SDL_Deleter> Renderer = nullptr;
}
namespace sdl2_Window
{
	std::unique_ptr<SDL_Window, sdl2_Deleter::SDL_Deleter> Window = nullptr;
}