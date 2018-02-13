#include "LoadingScreen.hpp"
#include "gRenderer.hpp"
#include "gScreenSize.hpp"

LoadingScreen::LoadingScreen()
{
	mLoading.loadFromFile("Data/hero.png");
	mLoading.setPos(SCREEN_WIDTH / 2 - mLoading.getWidth() / 2, SCREEN_HEIGHT / 2 - mLoading.getHeight() / 2);
}

void LoadingScreen::render()
{
	double angle = 0;
	while (mIsActive)
	{
		SDL_RenderClear(gRenderer); //clear screen
		mLoading.render(NULL,angle);
		SDL_RenderPresent(gRenderer); // update screen
		angle = angle + 1.25;
		if (angle >= 360)
			angle = 0;
	}
}
