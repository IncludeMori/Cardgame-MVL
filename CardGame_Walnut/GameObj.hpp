#pragma once

#include <memory>

#include <SDL.h>
#include "SDL_Deleter.hpp"

class GameObj
{
public:
	virtual void render(double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) = 0;
	virtual bool loadFromFile(const std::string &path) = 0;
protected:
	std::unique_ptr<SDL_Texture,sdl2_Deleter::SDL_Deleter> mTexture = nullptr;

	int mPosX = 0, mPosY = 0;
	int mWidth = 0, mHeight = 0;
};

