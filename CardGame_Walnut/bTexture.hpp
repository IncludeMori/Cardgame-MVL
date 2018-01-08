#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

#include "gRenderer.hpp"

class bTexture
{
public:
	bTexture();
	~bTexture();

	bool loadFromFile(std::string path);

	//Renders texture to screen at given point with various options 
	virtual void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void free();
private:
	int mPosX, mPosY;
	int mWidth, mHeight;

	SDL_Texture *mTexture;
};