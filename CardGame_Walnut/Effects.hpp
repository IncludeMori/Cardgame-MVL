#pragma once

#include <memory>
#include <vector>

#include "Card_Effects.hpp"

class Basic_Card;

class Deck;
class Field;
class Hand;


class Effects
{
public:
	Effects();
	~Effects();

	virtual bool activate(Basic_Card *card) = 0;
	virtual bool activate() = 0; //target(s)

	virtual bool setStuff(const std::shared_ptr<Deck> &deck, const std::shared_ptr<Hand> &hand, const std::shared_ptr<Field> &field, const std::shared_ptr<Field> &oppfield);

protected:
	std::shared_ptr<Deck> mDeck;
	std::shared_ptr<Hand> mHand;

	std::shared_ptr<Field> mField;
	std::shared_ptr<Field> mOpponentField;

	
};

