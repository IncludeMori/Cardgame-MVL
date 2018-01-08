//
// @Author: Moritz Volkenandt 
//
// Used for: Hero portrait, health 
//
#pragma once

#include "DefaultTexture.hpp"
#include "HeroHealth.hpp"

class Hero
{
public:
	Hero();
	Hero(int v,int amount);
	~Hero();

	void render();

	void dealDmg(int amount);

	bool MouseIsAbove();

	void setAlpha(Uint8 alpha);

	bool isAlive();

	int getX();
	int getY();
	int getWidth();
	int getHeight();

private:
	DefaultTexture mPortrait{ mPosX, mPosY };

	HeroHealth mHPSign;

	int mPosX, mPosY;
	bool mIsAlive;

};