#pragma once

#include <memory>
#include <vector>

#include "Card_Effects.hpp"

class BaseCard;

class Deck;
class Field;
class Hand;


class Effects
{
public:
	Effects();
	~Effects();

	virtual bool activate(BaseCard *card) = 0;
	virtual bool activate() = 0; //target(s)

	virtual bool setStuff(const std::weak_ptr<Deck> &deck, const std::weak_ptr<Hand> &hand, const std::weak_ptr<Field> &field, const std::weak_ptr<Field> &oppfield);

protected:
	std::weak_ptr<Deck> mDeck;
	std::weak_ptr<Hand> mHand;

	std::weak_ptr<Field> mField;
	std::weak_ptr<Field> mOpponentField;

	
};

