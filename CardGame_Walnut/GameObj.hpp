#pragma once

#include <memory>

#include <SDL.h>
#include "SDL_Deleter.hpp"

class GameObj
{
public:
	GameObj() = default;
	GameObj(int x, int y) : mPosX(x), mPosY(y) {};

	virtual void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) = 0;
	virtual void loadFromFile(const std::string &path);

	void setPos(int x, int y);
	int getPosX(), getPosY();
	int getWidth(), getHeight();


protected:
	std::unique_ptr<SDL_Texture,sdl2_Deleter::SDL_Deleter> mTexture = nullptr;

	SDL_Rect mDstRect;
	int mPosX = 0, mPosY = 0;
	int mWidth = 0, mHeight = 0;
};

