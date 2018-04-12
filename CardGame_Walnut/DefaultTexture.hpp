//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: basic game assets
//
#pragma once

#include <SDL_image.h>
#include <string>
#include <memory>

#include "SDL_Deleter.hpp"

class DefaultTexture
{
public:
	DefaultTexture() = default;
	explicit DefaultTexture(int x, int y) : mPosX(x), mPosY(y) {};
	DefaultTexture(const std::string &path, int x = 0, int y = 0);

	//Loads Image from "path"
	virtual bool loadFromFile(std::string path);

	//Renders texture to screen at given point with various options 
	virtual void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//set functions
	void setPos(int x, int y);

    void setColor(Uint8 red, Uint8 green, Uint8 blue); //changes color
    void setBlendMode(SDL_BlendMode blending); //changes blend mode
	void setAlpha(Uint8 alpha); //changes alpha
	
	//get functions
	int getWidth();
	int getHeight();

	int getX();
	int getY();

	bool isEmpty();

protected:
	std::unique_ptr<SDL_Texture, sdl2_Deleter::SDL_Deleter> mTexture = nullptr; //actual texture
	SDL_Rect mDstRect;

	int mWidth = 0;
	int mHeight = 0;

	int mPosX = 0;
	int mPosY = 0;
};