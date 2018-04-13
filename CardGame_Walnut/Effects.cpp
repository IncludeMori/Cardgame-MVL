#include "Effects.hpp"

#include "Deck.hpp"
#include "Hand.hpp"
#include "Field.hpp"

Effects::Effects()
{
}


Effects::~Effects()
{
}

bool Effects::setStuff(const std::weak_ptr<Deck> &deck, const std::weak_ptr<Hand> &hand, const std::weak_ptr<Field> &field, const std::weak_ptr<Field> &oppfield)
{
	mField = field;
	mDeck = deck;
	mHand = hand;
	mOpponentField = oppfield;
	return true;
}