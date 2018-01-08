#pragma once
#include "DefaultTexture.hpp"
class EnergySign :
	public DefaultTexture
{
public:
	EnergySign();
	~EnergySign();

	void setNotAvailable();
	void setAvailable();

	bool isAvailable();
protected:
	bool mIsAvailable;
};

