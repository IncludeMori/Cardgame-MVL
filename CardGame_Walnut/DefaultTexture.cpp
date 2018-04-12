#include "DefaultTexture.hpp"

#include <iostream>

#include "Renderer.hpp"
using namespace sdl2_Renderer;


DefaultTexture::DefaultTexture(const std::string &path, int x, int y)
{
	loadFromFile(path);
}

bool DefaultTexture::loadFromFile(std::string path)
{
	std::cout << "Loading: " << path << std::endl;
	
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		__debugbreak();
		throw std::runtime_error("Unable to load image at:" + path + "  Error:" + IMG_GetError());
	}
	else
	{
		//neutral colorkey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer.get(), loadedSurface);
		if (!newTexture)
		{
			throw std::runtime_error("Failed to create texture from surface at " +path+"    Sdl_Error:" + SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	mTexture.reset(newTexture);

	//Set rendering space and render to screen
	this->mDstRect = { mPosX,mPosY, mWidth, mHeight };

	return mTexture != nullptr;
}

void DefaultTexture::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (clip)
	{
		this->mDstRect.w = clip->w;
		this->mDstRect.h = clip->h;
	}

	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &this->mDstRect, angle, center, flip); // renders texture to screen
}

void DefaultTexture::setPos(int x, int y)
{
	this->mPosX = x;
	this->mPosY = y;

	mDstRect.x = x;
	mDstRect.y = y;
}

void DefaultTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture.get(), red, green, blue);
}

void DefaultTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture.get(), blending);
}

void DefaultTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture.get(), alpha);

}

bool DefaultTexture::isEmpty()
{
	if (mTexture) { return false; }
	else { return true; }
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