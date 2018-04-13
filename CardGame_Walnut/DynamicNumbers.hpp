#pragma once

#include <SDL_image.h>
#include <string>

#include "GameObj.hpp"

class DynamicNumbers : public GameObj
{
public:
	DynamicNumbers();
	
	//Renders texture to screen at given point with various options 
	void render(SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) override;
	void update();

	void changeData(int number);
	
	void setSDLTexture(SDL_Texture *Texture,int width,int height);

protected:
	SDL_Rect mNumbers[12];

	int mData;
};

