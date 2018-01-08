//
// @Author: Moritz Volkenandt 
//
// Ingame resource, needed to play a card
//
#pragma once

#include "HeroHealth.hpp"
#include "EnergyInterface.hpp"
#include "DefaultTexture.hpp"

class Resource : public HeroHealth
{
public:
	using HeroHealth::setPos;
	Resource();
	
	void removeAv(int amount);

	void setPos(int x, int y, int who);

	void render(double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void increase(); // mAmount++
	void decrease(); // mAmount--

	int getAmount();
	int getAvailable();

private:
	const int mMax_Amount = 10;

	EnergyInterface mEnergyInterface;
	DefaultTexture mBackground;

};