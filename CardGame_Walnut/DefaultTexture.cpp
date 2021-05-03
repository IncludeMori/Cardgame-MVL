#include "DefaultTexture.hpp"
#include "Renderer.hpp"

using namespace sdl2_Renderer;


void DefaultTexture::render(SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), nullptr, &this->mDstRect, angle, center, flip); 
}
