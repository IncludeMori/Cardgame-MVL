//
// @Author: Moritz Volkenandt 
//
// Purpose: Render dynamic number to screen(used for health, atk, etc)
//
#pragma once

#include <SDL_image.h>
#include <string>

class HeroHealth
{
public:
	HeroHealth();
	~HeroHealth();

	//Renders texture to screen at given point with various options 
	void render(double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void update();

	void changeData(int number);
	void add(int amount);
	void setPos(int x, int y);

	int getCurrentData();

	int getHeight();
	int getWidth();

	void free();

protected:
	SDL_Rect mNumbers[12];

	//Loads Image from "path"
	bool loadFromFile(std::string path);

	SDL_Texture* mTexture; //texture


	int mBaseStat, mCurrentStat;
	int mPosX, mPosY;
	int mWidth, mHeight;
};