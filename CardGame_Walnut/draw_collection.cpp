#pragma once
#include "draw_collection.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

void drawCardField()
{
	SDL_SetRenderDrawColor(Renderer.get(), 100, 100, 100, 100);

	SDL_Rect X = { 180,100,SCREEN_WIDTH / 2+20,SCREEN_HEIGHT - 120 };
	
	SDL_RenderDrawRect(Renderer.get(),&X);


	//reset
	SDL_SetRenderDrawColor(Renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
}

void drawDeckField()
{
	SDL_SetRenderDrawColor(Renderer.get(), 100, 100, 100, 100);

	SDL_Rect X = { SCREEN_WIDTH / 2 + 250,100,SCREEN_WIDTH / 3+50,SCREEN_HEIGHT - 120 };
	SDL_RenderDrawRect(Renderer.get(), &X);

	

	//reset
	SDL_SetRenderDrawColor(Renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

}
