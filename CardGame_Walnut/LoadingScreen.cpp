#include "LoadingScreen.hpp""
#include "gScreenSize.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

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
		SDL_RenderClear(Renderer.get()); //clear screen
		mLoading.render(nullptr,angle);
		SDL_RenderPresent(Renderer.get()); // update screen
		angle = angle + 1.25;
		if (angle >= 360)
			angle = 0;
	}
}
