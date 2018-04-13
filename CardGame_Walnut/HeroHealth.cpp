#include "HeroHealth.hpp"

#include <iostream>

#include "Renderer.hpp"
using namespace sdl2_Renderer;

HeroHealth::HeroHealth()
{
	loadFromFile("Data/numbers.png");

	int x = 0, y = 0, w = 35, h = 35;
	for (int i = 1; i < 9; i++)
	{
		mNumbers[i] = { x,y,w,h };
		x += 35;

		if (i == 5) { x = 0; y += 35; }
	}
	mNumbers[0] = { x + 35,y,w,h };
	mNumbers[10] = { 0,y + 35,w,h };
	mNumbers[11] = { 35,70,35,35 };

	mWidth = 35;
	mHeight = 35;
}

void HeroHealth::render(SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mHeight, mWidth };

	if (mCurrentValue < 10)
	{
		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[mCurrentValue], &renderQuad, angle, center, flip); // renders texture to screen
	}
	// 9 < x < 100
	else if (mCurrentValue > 9 && mCurrentValue < 100) {

		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[mCurrentValue/10], &renderQuad, angle, center, flip); // renders texture to screen

		renderQuad.x += mWidth-5;

		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[mCurrentValue%10], &renderQuad, angle, center, flip); // renders texture to screen

	}
	else // >90
	{
		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[9], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += mWidth-5;
		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[9], &renderQuad, angle, center, flip); // renders texture to screen
	}
}

void HeroHealth::changeBaseDataTo(int n)
{
	mBaseValue = n;
}
void HeroHealth::changeDataTo(int n)
{
	mCurrentValue = n;
}
void HeroHealth::increase(int amount)
{
	mCurrentValue += amount;
}
int HeroHealth::getValue()
{
	return mCurrentValue;
}