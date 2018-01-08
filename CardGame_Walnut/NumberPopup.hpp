#pragma once

#include <vector>

#include "DefaultTexture.hpp"
#include "HeroHealth.hpp"

#include "DynamicNumbers.hpp"




class NumberPopup 
{
public:
	NumberPopup();
	~NumberPopup();

	void render();
	void update();

	void add(int amount, int posX, int posY);

	void free();

private:
	// mehrere karten bekommen gleichzeitig schaden?
	std::vector<int> mPosX, mPosY, mStat;
	DynamicNumbers CurrentNumbers;
	
	DefaultTexture mNumberBackground;

	std::vector<SDL_TimerID> myTimer; //

	SDL_Texture *mNumberTexture;
	int mWidth, mHeight;
	bool loadNumberTexture();
};

