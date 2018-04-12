#include "SDL_init.hpp"

// SDL libs
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_main.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Renderer.hpp"

using namespace sdl2_Window;
using namespace sdl2_Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////
bool sdl2_Init::startSDL(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const std::string &WINDOW_NAME)
{
	//INIT SDL (everything)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		std::cout << "SDL_Init failed. Error msg:" << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		//Create the main window
		Window.reset(SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
		if (!Window)
		{
			std::cout << "SDL_Create Window failed. Error msg:" << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			//Create renderer, hardware(GPU)
			Renderer.reset(SDL_CreateRenderer(Window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
			if (!Renderer)
			{
				std::cout << "Renderer creation failed. Error msg:" << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				//neutral draw color
				SDL_SetRenderDrawColor(Renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

				//INIT PNG
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_Image creation failed. Error msg:" << IMG_GetError() << std::endl;
					return false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					std::cout << "SDL_TTF init failed. Error msg:" << TTF_GetError() << std::endl;
					return false;
				}

				//INIT Audio
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 20000) < 0)
				{
					std::cout << "SDL_Mixer creation failed. Error msg:" << Mix_GetError() << std::endl;
					return false;
				}

			}
		}
	}
	return true;
}
void sdl2_Init::closeSDL()
{
	Window = nullptr;
	Renderer = nullptr;

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_VideoQuit();
	SDL_AudioQuit();
	SDL_Quit();
}