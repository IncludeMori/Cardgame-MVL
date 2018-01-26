//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: basic game assets
//
#pragma once

// SDL libs
#include <SDL_image.h>
#include <string>

class DefaultTexture
{
public:
	DefaultTexture();
	DefaultTexture(int x, int y);
	DefaultTexture(std::string &path);
	~DefaultTexture();

	//Loads Image from "path"
	bool loadFromFile(std::string path);

	//Renders texture to screen at given point with various options 
	virtual void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//set functions
	virtual void setPos(int x, int y);

	//
	void setColor(Uint8 red, Uint8 green, Uint8 blue); //changes color
	void setBlendMode(SDL_BlendMode blending); //changes blend mode
	void setAlpha(Uint8 alpha); //changes alpha
	

	//get functions
	int getWidth();
	int getHeight();

	int getX();
	int getY();

	bool isEmpty();

	//Deallocates texture, frees memory
	void free();

protected:

	SDL_Texture* mTexture; //actual texture

	//image data
	int mWidth;
	int mHeight;

	int mPosX;
	int mPosY;
};