#include "draw.hpp"


void drawLines()
{
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);


	//SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT - SCREEN_HEIGHT / 4, SCREEN_WIDTH, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
	SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT - 2*(SCREEN_HEIGHT / 4), SCREEN_WIDTH, SCREEN_HEIGHT - 2*(SCREEN_HEIGHT / 4));
	//SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT - 3 * (SCREEN_HEIGHT / 4), SCREEN_WIDTH, SCREEN_HEIGHT - 3*(SCREEN_HEIGHT / 4));
	//SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT - 4 * (SCREEN_HEIGHT / 4), SCREEN_WIDTH, SCREEN_HEIGHT - 4*(SCREEN_HEIGHT / 4));

	//DECK LINE
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH - SCREEN_WIDTH / 6, 0, SCREEN_WIDTH - SCREEN_WIDTH / 6, SCREEN_HEIGHT);


	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
	//SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 4, 0, SCREEN_WIDTH / 4, SCREEN_HEIGHT);
	//SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH -SCREEN_WIDTH/ 4, 0, SCREEN_WIDTH - SCREEN_WIDTH/4, SCREEN_HEIGHT);

	//Effect Field
	SDL_RenderDrawLine(gRenderer, 300, 0, 300, SCREEN_HEIGHT);
	SDL_Rect rect = { 75,SCREEN_HEIGHT/2-300/2,200,300 };
	SDL_RenderDrawRect(gRenderer, &rect);

	//resett
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
}

void drawField()
{

	//....
}
void drawRect(SDL_Rect &rect)
{
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);

	SDL_RenderDrawRect(gRenderer, &rect);
	//reset
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}