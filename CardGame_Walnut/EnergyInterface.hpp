#pragma once

#include "DefaultTexture.hpp"
#include "EnergySign.hpp"

class EnergyInterface
{
public:
	EnergyInterface();
	EnergyInterface(int v); //player or opponent, use enum
	~EnergyInterface();

	void render();

	void addEnergy(int amount);
	void subEnergy(int amount);

	void increase();
	void decrease();

	void init(int who);

private:
	int MAX_ENERGY = 10;
	EnergySign mEnergy[10];
	int mPosX[10], mPosY[10];

	int currentMaxEnergy;
	int currentEnergy;

	void update();

	DefaultTexture mBackground;

};

