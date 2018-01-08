#pragma once

#include <SDL_image.h>
#include <string>

class DynamicNumbers
{
public:
	DynamicNumbers();
	~DynamicNumbers();

	//Renders texture to screen at given point with various options 
	void render(double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void update();

	void changeData(int number);
	void setPos(int x, int y);
	void setSDLTexture(SDL_Texture *Texture,int width,int height);

	int getHeight();
	int getWidth();

	void free();

protected:
	SDL_Rect mNumbers[12];

	//Loads Image from "path"
	bool loadFromFile(std::string path);

	SDL_Texture *mTexture = nullptr; //texture

	int mPosX, mPosY;
	int mWidth, mHeight;
	int mData;
};

