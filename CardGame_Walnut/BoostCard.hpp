#pragma once
//#include "Battlecry.hpp"

#include <vector>
#include <memory>

#include "Battlecry.hpp"
#include "Deathwish.hpp"
#include "ModifyStatsEffect.hpp"

class MonsterCard;

class Deck;
class Field;
class Hand;


class BoostCard 
	:public Battlecry, public Deathwish
{
public:
	BoostCard();
	BoostCard(eTargetType target, eTargetTypeSpec target_spec, eTargetStatType stat, int amount);
	~BoostCard();

	bool activate(BaseCard *card); //self
	bool activate(); //target(s)

private:
	int mAmount = 0;
	eTargetType mTarget = eTargetType::ERROR;
	eTargetTypeSpec mTargetSpec = eTargetTypeSpec::ERROR;
	eTargetStatType mStat = eTargetStatType::ERROR;

};

