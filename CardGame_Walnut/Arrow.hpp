#pragma once

#include "DefaultTexture.hpp"

class Arrow : public DefaultTexture
{
public:
	Arrow() = default;

	void render(SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

	void move(int x, int y);

	bool isActive();
	void setActive();
	void setInactive();

private:
	bool mActive = false;
};