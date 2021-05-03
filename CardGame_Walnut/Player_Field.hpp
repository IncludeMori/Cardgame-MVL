#pragma once

#include <vector>

#include "MonsterCard.hpp"
#include "Arrow.hpp"
#include "draw.hpp"
#include <memory>

#include "Field.hpp"
#include "Opponent_Field.hpp"
#include "Hero.hpp"

#include "EffectField.hpp"

#include "NumberPopup.hpp"



//delete
#include <iostream>

class Player_Field : public Field
{
public:
	Player_Field();
	~Player_Field();

	bool update();
	void render();

	void addCard(const std::shared_ptr<BaseCard> &card);
	void addEffectCard(const std::shared_ptr<BaseCard> &card);

	bool isInside(int x, int y); // moving card from Player_Hand is inside field? -> player wants to play card

	void setField(const std::weak_ptr<Opponent_Field>& OppField);
	void setHero(const std::weak_ptr<Hero>& hero);

private:
	int hover = -1;

	int mActiveCard = 0;

	bool battlecry_active = false;
	int ba_card = -1;

	EffectField Effect_Field;

	std::weak_ptr<Opponent_Field> mOppField;
	std::weak_ptr<Hero> mOppHero;
	//std::shared_ptr<Opponent_Field> mOField; //pointer->Opponent field
	bool misUsingACard;

	Arrow TargetCard;

	NumberPopup mFieldNumberPopups;

	//dev
	void Dev_printCardPosIndex()
	{
		for (int i = 0; i < MAX_SIZE; i++)
			std::cout << "Card:" << i << "at index:" << mCardPosIndex[i] << std::endl;
	}
};