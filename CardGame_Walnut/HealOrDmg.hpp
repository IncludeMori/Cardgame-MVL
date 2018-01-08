#pragma once

#include "Effects.hpp"

#include "Basic_Card.hpp"

class HealOrDmg : public Effects
{
public:
	HealOrDmg();
	HealOrDmg(int amount);
	~HealOrDmg();

	bool activate(Basic_Card *card);
	bool activate();

private:
	int mAmount;
};

