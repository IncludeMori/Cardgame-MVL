#pragma once

#include <vector>

#include "Default_Card.hpp"
#include "Arrow.hpp"
#include "draw.hpp"
#include <memory>

#include "Field.hpp"
#include "Opponent_Field.hpp"
#include "Hero.hpp"

#include "EffectField.hpp"

#include "NumberPopup.hpp"



class Player_Field : public Field
{
public:
	Player_Field();
	~Player_Field();

	bool update();
	void render();

	void addCard(const std::shared_ptr<Basic_Card> &card);
	void addEffectCard(const std::shared_ptr<Basic_Card> &card);

	bool isInside(int x, int y); // moving card from Player_Hand is inside field? -> player wants to play card

	void setField(const std::shared_ptr<Opponent_Field>& OppField);
	void setHero(const std::shared_ptr<Hero>& hero);

private:
	int mActiveCard = 0;

	bool battlecry_active = false;
	int ba_card = -1;

	EffectField Effect_Field;

	std::shared_ptr<Opponent_Field> mOppField;
	std::shared_ptr<Hero> mOppHero;
	//std::shared_ptr<Opponent_Field> mOField; //pointer->Opponent field
	bool misUsingACard;

	Arrow TargetCard;

	NumberPopup mFieldNumberPopups;


	void updateFieldWithNewCard(int index);
	void updatePositions();
};