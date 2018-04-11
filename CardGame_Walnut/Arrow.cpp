#include "Arrow.hpp"

void Arrow::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (clip != nullptr)
	{
		this->mDstRect.w = clip->w;
		this->mDstRect.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, mTexture.get(), clip, &this->mDstRect, angle, center, flip); // renders texture to screen
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