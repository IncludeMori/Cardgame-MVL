#include "EnergyInterface.hpp"

#include "gScreenSize.hpp"


EnergyInterface::EnergyInterface()
{
	currentEnergy = 0;
	currentMaxEnergy = 0;
	mBackground.loadFromFile("Data/Hero_Interface/Background_Mana.png");
}
EnergyInterface::EnergyInterface(int v)
{
	mBackground.loadFromFile("Data/Hero_Interface/Background_Mana.png");
	init(v);
}


EnergyInterface::~EnergyInterface()
{
}

void EnergyInterface::render()
{
	mBackground.render();
	for (int i = 0; i < currentMaxEnergy; i++)
		mEnergy[i].render();
}

void EnergyInterface::addEnergy(int amount)
{
	currentEnergy += amount;
	if (currentEnergy > 10)
		currentEnergy = 10;

	update();
}

void EnergyInterface::subEnergy(int amount)
{
	currentEnergy -= amount;
	if (currentEnergy < 0)
		currentEnergy = 0;

	update();
}

void EnergyInterface::increase()
{
	currentMaxEnergy++;
	if (currentMaxEnergy > 10)
		currentMaxEnergy = 10;

	currentEnergy = currentMaxEnergy;
	update();
	
}
void EnergyInterface::decrease()
{
	currentMaxEnergy--;

	currentEnergy = currentMaxEnergy;
	update();
}

void EnergyInterface::init(int who)
{
	currentEnergy = 0;
	currentMaxEnergy = 0;

	int x, y;
	if (who == 0)
	{
		x = SCREEN_WIDTH / 2 + 80;
		y = SCREEN_HEIGHT - SCREEN_HEIGHT / 4+90;
	}
	else
	{
		x = SCREEN_WIDTH / 2 + 80;
		y = SCREEN_HEIGHT - 3 * (SCREEN_HEIGHT / 4)-60;
	}

	int shiftX = 55;
	y = y - 10;
	//x = x - 5;
	for (int i = 0; i < 10; i++)
	{
		mPosX[i] = x + (i*shiftX);
		mPosY[i] = y;
	}



	for (int i = 0; i < 10; i++)
	{
		mEnergy[i].loadFromFile("Data/Hero_Interface/energy.png");
		mEnergy[i].setPos(mPosX[i], mPosY[i]);
	}

	mBackground.setPos(x-5, y-10);



}
void EnergyInterface::update()
{
	
	for (int i = 0; i < 10; i++)
		if (i < currentEnergy)
			mEnergy[i].setAvailable();
		else
			mEnergy[i].setNotAvailable();


			
}
