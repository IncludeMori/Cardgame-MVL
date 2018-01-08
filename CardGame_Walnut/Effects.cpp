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

bool Effects::setStuff(const std::shared_ptr<Deck> &deck, const std::shared_ptr<Hand> &hand, const std::shared_ptr<Field> &field, const std::shared_ptr<Field> &oppfield)
{
	mField = field;
	mDeck = deck;
	mHand = hand;
	mOpponentField = oppfield;
	return true;
}