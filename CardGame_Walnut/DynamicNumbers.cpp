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
DynamicNumbers::~DynamicNumbers()
{
	free();
}

void DynamicNumbers::render(double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mHeight, mWidth };

	if (mData < 10)
	{
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[mData], &renderQuad, angle, center, flip); // renders texture to screen
	}
	// 9 < x < 100
	else if (mData > 9 && mData < 100) {

		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[mData / 10], &renderQuad, angle, center, flip); // renders texture to screen

		renderQuad.x += mWidth - 5;

		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[mData % 10], &renderQuad, angle, center, flip); // renders texture to screen

	}
	else // >90
	{
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[9], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += mWidth - 5;
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[9], &renderQuad, angle, center, flip); // renders texture to screen
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

void DynamicNumbers::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
}

void DynamicNumbers::setSDLTexture(SDL_Texture * Texture,int width,int height)
{
	free();
	//mWidth = width;
	//mHeight = height;
	mTexture = Texture;
}

int DynamicNumbers::getHeight()
{
	return mHeight;
}
int DynamicNumbers::getWidth()
{
	return mWidth;
}


void DynamicNumbers::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}

//protected

bool DynamicNumbers::loadFromFile(std::string path)
{
	std::cout << "Loading: " << path << std::endl;
	//delete preexisting textures
	free();

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
	mTexture = newTexture;
	return mTexture != nullptr;
}