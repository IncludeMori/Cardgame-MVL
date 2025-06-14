#pragma once

#include "Field.hpp"
#include "gScreenSize.hpp"
#include "Hero.hpp"


class Opponent_Field : public Field
{
public:
	Opponent_Field();
	~Opponent_Field();

	void update();

	//using Field::addCard;
	void addCard(const std::shared_ptr<BaseCard>& card, int index);
	void attack();

	bool ChooseCard();

	void setField(const std::weak_ptr<Field>& field);
	void setHero(const std::weak_ptr<Hero>& hero);

private:
	std::weak_ptr<Hero> mPlayerHero;
	std::weak_ptr<Field> mPlayerField;
	//std::shared_ptr<Player_Field> mPlayerField;
	
};