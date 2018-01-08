#pragma once
//#include "Battlecry.hpp"

#include <vector>
#include <memory>

#include "Battlecry.hpp"
#include "Deathwish.hpp"

#include "Card_Effects.hpp"

class Default_Card;

class Deck;
class Field;
class Hand;


class BoostCard 
	:public Battlecry, public Deathwish
{
public:
	BoostCard();
	BoostCard(eTarget target, eTarget_spec target_spec, eStat stat, int amount);
	~BoostCard();

	bool activate(Basic_Card *card); //self
	bool activate(); //target(s)

private:
	int mAmount = 0;
	eTarget mTarget = eTarget::ERROR;
	eTarget_spec mTarget_spec = eTarget_spec::ERROR;
	eStat mStat = eStat::ERROR;
};

