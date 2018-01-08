#pragma once

#include "DefaultTexture.hpp"
#include "Rarity.hpp"

class Frame : public DefaultTexture
{
public:
	Frame();
	~Frame();

	void load(Rarity rarity,bool big);
};

