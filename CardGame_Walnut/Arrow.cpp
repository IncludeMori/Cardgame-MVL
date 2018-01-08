#include "Arrow.hpp"

Arrow::Arrow()
{
	mActive = false;
	mPosX = 0;
	mPosY = 0;
}
Arrow::~Arrow()
{
	free();
}

void Arrow::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip); // renders texture to screen
}


void Arrow::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
}
void Arrow::move(int x, int y)
{
	mPosX += x;
	mPosY += y;
}

bool Arrow::isActive()
{
	return mActive;
}

void Arrow::setActive()
{
	mActive = true;
}

void Arrow::setInactive()
{
	mActive = false;
}