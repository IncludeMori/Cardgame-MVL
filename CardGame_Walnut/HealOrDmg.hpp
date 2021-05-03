#pragma once

#include "Effects.hpp"

#include "BaseCard.hpp"

class HealOrDmg : public Effects
{
public:
	HealOrDmg();
	HealOrDmg(int amount);
	~HealOrDmg();

	bool activate(BaseCard *card);
	bool activate();

private:
	int mAmount;
};

