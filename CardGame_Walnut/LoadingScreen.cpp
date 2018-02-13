#include "LoadingScreen.hpp"
#include "gRenderer.hpp"
#include "gScreenSize.hpp"

LoadingScreen::LoadingScreen()
{
	x.loadFromFile("Data/hero.png");
	x.setPos(SCREEN_WIDTH / 2 - x.getWidth() / 2, SCREEN_HEIGHT / 2 - x.getHeight() / 2);
}

void LoadingScreen::render()
{
	double angle = 0;
	while (y)
	{
		SDL_RenderClear(gRenderer); //clear screen
		x.render(NULL,angle);
		SDL_RenderPresent(gRenderer); // update screen
		angle = angle + 1.25;
		if (angle >= 360)
			angle = 0;
	}
}
