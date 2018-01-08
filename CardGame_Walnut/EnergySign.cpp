#include "EnergySign.hpp"



EnergySign::EnergySign()
{
	mIsAvailable = false;
}


EnergySign::~EnergySign()
{
}

void EnergySign::setAvailable()
{
	mIsAvailable = true;
	setAlpha(255);
}
void EnergySign::setNotAvailable()
{
	mIsAvailable = false;
	setAlpha(255/4);
}

bool EnergySign::isAvailable()
{
	return mIsAvailable;
}