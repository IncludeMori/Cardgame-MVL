//
// @Author: Moritz Volkenandt 
//
// Purpose: Render dynamic number to screen(used for health, atk, etc)
//
#pragma once

#include <string>
#include <memory>

#include "GameObj.hpp"

#include <SDL_image.h>
#include "SDL_Deleter.hpp"

class HeroHealth : public GameObj
{
public:
	HeroHealth();
	HeroHealth(int base_value, int start_value) : mBaseValue(base_value),mCurrentValue(start_value) {};

	//Renders texture to screen at given point with various options 
	void render(SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

	void changeBaseDataTo(int n);
	void changeDataTo(int n);
	void increase(int amount);

	int getValue();

protected:
	int mBaseValue = 0;
	int mCurrentValue = 0;

	SDL_Rect mNumbers[12];

	//Loads Image from "path"
	//void initNumbers();

};