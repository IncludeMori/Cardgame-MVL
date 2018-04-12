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

void HeroHealth::render(double angle, SDL_Point* center, SDL_RendererFlip flip)
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
void HeroHealth::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
}

int HeroHealth::getValue()
{
	return mCurrentValue;
}
int HeroHealth::getHeight()
{
	return mHeight;
}
int HeroHealth::getWidth()
{
	return mWidth;
}


//protected

bool HeroHealth::loadFromFile(const std::string &path)
{
	std::cout << "Loading: " << path << std::endl;
	//delete preexisting textures

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//neutral colorkey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer.get(), loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Failed to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	mTexture.reset(newTexture);
	return mTexture != nullptr;
}