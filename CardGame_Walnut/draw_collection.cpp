#pragma once
#include "draw_collection.hpp"

void drawCardField()
{
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);

	SDL_Rect X = { 180,100,SCREEN_WIDTH / 2+20,SCREEN_HEIGHT - 120 };
	
	SDL_RenderDrawRect(gRenderer,&X);


	//reset
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void drawDeckField()
{
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);

	SDL_Rect X = { SCREEN_WIDTH / 2 + 250,100,SCREEN_WIDTH / 3+50,SCREEN_HEIGHT - 120 };
	SDL_RenderDrawRect(gRenderer, &X);

	

	//reset
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

}
