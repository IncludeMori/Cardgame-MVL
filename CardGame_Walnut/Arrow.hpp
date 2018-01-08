#pragma once

#include "DefaultTexture.hpp"
#include "gRenderer.hpp"

class Arrow : public DefaultTexture
{
public:
	Arrow();
	~Arrow();

	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void setPos(int x, int y);
	void move(int x, int y);
	bool isActive();
	
	void setActive();
	void setInactive();

private:
	int mPosX, mPosY;
	bool mActive;
};