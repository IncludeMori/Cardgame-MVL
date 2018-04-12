#include "DynamicNumbers.hpp"



#include <iostream>

#include "Renderer.hpp"

using namespace sdl2_Renderer;

DynamicNumbers::DynamicNumbers()
{
	
	mTexture = nullptr;
	loadFromFile("Data/BigCard_Interface/numbers_big.png");

	int x = 0, y = 0, w = 50, h = 50;
	for (int i = 1; i < 9; i++)
	{
		mNumbers[i] = { x,y,w,h };
		x += 50;

		if (i == 5) { x = 0; y += 50; }
	}
	mNumbers[0] = { x + 50,y,w,h };
	mNumbers[10] = { 0,y + 50,w,h };
	mNumbers[11] = { 50,100,50,50 };

	mPosX = 0;
	mPosY = 0;
	mWidth = 50;
	mHeight = 50;
	
	
	/*mTexture = nullptr;
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

	mPosX = 0;
	mPosY = 0;
	mWidth = 35;
	mHeight = 35;
	*/
	mData = 0;
}


void DynamicNumbers::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mHeight, mWidth };

	if (mData < 10)
	{
		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[mData], &renderQuad, angle, center, flip); // renders texture to screen
	}
	// 9 < x < 100
	else if (mData > 9 && mData < 100) {

		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[mData / 10], &renderQuad, angle, center, flip); // renders texture to screen

		renderQuad.x += mWidth - 5;

		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[mData % 10], &renderQuad, angle, center, flip); // renders texture to screen

	}
	else // >90
	{
		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[9], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += mWidth - 5;
		SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &mNumbers[9], &renderQuad, angle, center, flip); // renders texture to screen
	}
}


void DynamicNumbers::update()
{
	//update number if CurrentStats are different
}


void DynamicNumbers::changeData(int number)
{
	mData = number;
}


void DynamicNumbers::setSDLTexture(SDL_Texture * Texture,int width,int height)
{
	mTexture.reset(Texture);
}


