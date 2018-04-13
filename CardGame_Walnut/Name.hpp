#pragma once

#include <string>

#include "TTF_Text.hpp"
#include "Who.hpp"
#include "DefaultTexture.hpp"

class Name : public TTF_Text
{
public:
	Name();
	~Name();

	void init(who::type o,const std::string &name);
	void setName(const std::string &name);

	void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	DefaultTexture mBackground;
};

