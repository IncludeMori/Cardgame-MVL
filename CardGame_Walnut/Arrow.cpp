#include "Arrow.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

void Arrow::render(SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), nullptr, &this->mDstRect, angle, center, flip); // renders texture to screen
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