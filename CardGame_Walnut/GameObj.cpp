
#include <SDL_image.h>
#include <iostream>

#include "GameObj.hpp"
#include "Renderer.hpp"

using namespace sdl2_Renderer;

void GameObj::loadFromFile(const std::string &path)
{
	std::cout << "Loading: " << path.c_str() << std::endl;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface)
	{
		throw std::runtime_error("Unable to load image at:" + path + "  Error:" + IMG_GetError());
	}
	else
	{
		//neutral colorkey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
		std::unique_ptr<SDL_Texture, sdl2_Deleter::SDL_Deleter> newTexture(SDL_CreateTextureFromSurface(Renderer.get(), loadedSurface));
		if (!newTexture)
		{
			throw std::runtime_error("Failed to create texture from surface at " + path + "    Sdl_Error:" + SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		//move ptr to member
		mTexture = std::move(newTexture);
	}
	//Set rendering space
	this->mDstRect = { mPosX,mPosY, mWidth, mHeight };
	
}

void GameObj::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), nullptr, &this->mDstRect, angle, center, flip);
}

void GameObj::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(getTexture(), red, green, blue);
}

void GameObj::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(getTexture(), blending);
}

void GameObj::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(getTexture(), alpha);
}

void GameObj::setPos(int x, int y)
{
	this->mPosX = x;
	this->mPosY = y;
	this->mDstRect = { mPosX,mPosY, mWidth, mHeight };
}
void GameObj::move(int x, int y)
{
	this->mPosX += x;
	this->mPosY += y;

	this->mDstRect.x = this->mPosX;
	this->mDstRect.y = this->mPosY;
}

int GameObj::getPosX()
{
	return mPosX;
}
int GameObj::getPosY()
{
	return mPosY;
}

int GameObj::getWidth()
{
	return mWidth;
}
int GameObj::getHeight()
{
	return mHeight;
}

bool GameObj::isEmpty()
{
	if (!mTexture) 
		return false;
	else
		return true;
}
