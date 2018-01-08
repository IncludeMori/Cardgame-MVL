#include "DefaultTexture.hpp"

#include <iostream>

extern SDL_Renderer *gRenderer;

DefaultTexture::DefaultTexture()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
	mPosX = 0;
	mPosY = 0;
}
DefaultTexture::DefaultTexture(int x, int y)
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
	mPosX = x;
	mPosY = y;
	int lol = 0;
}
DefaultTexture::~DefaultTexture()
{
	free();
}

bool DefaultTexture::loadFromFile(std::string path)
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
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
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
	std::cout << mTexture << std::endl;
	return mTexture != NULL;
}

void DefaultTexture::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mWidth, mHeight };


	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip); // renders texture to screen

}

void DefaultTexture::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
}

void DefaultTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void DefaultTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void DefaultTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);

}

bool DefaultTexture::isEmpty()
{
	if (mTexture == nullptr) { return true; }
	else { return false; }
}
int DefaultTexture::getWidth()
{
	return mWidth;
}

int DefaultTexture::getHeight()
{
	return mHeight;
}

int DefaultTexture::getX()
{
	return mPosX;
}

int DefaultTexture::getY()
{
	return mPosY;
}


void DefaultTexture::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
		mPosX = 0;
		mPosY = 0;
	}
}