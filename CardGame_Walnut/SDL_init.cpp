#include "SDL_init.hpp"

// SDL libs
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_main.h>
#include <SDL_ttf.h>


extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;
///////////////////////////////////////////////////////////////////////////////////////////////////
bool SDL_init::SDLinit(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const std::string WINDOW_NAME)
{
	bool success = true;

	//INIT SDL (everything)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// NOT NEEDED?
		//srand(SDL_GetTicks());

		//Create the main window
		gWindow = SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Window creation failed -> SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer, hardware(GPU)
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr)
			{
				printf("Renderer creation failed -> SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//neutral draw color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//INIT PNG
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image creation failed -> SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//INIT Audio
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer creation failed -> SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

			}
		}
	}

	return success;
}
void SDL_init::SDLclose()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = nullptr;
	gRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	SDL_VideoQuit();
	SDL_AudioQuit();
}