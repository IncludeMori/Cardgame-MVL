#include "Opponent_Deck.hpp"

#include <iostream>
#include "gScreenSize.hpp"

#include "Opponent_Hand.hpp"
#include "Opponent_Field.hpp"
Opponent_Deck::Opponent_Deck()
{
	mPosX = SCREEN_WIDTH - SCREEN_WIDTH / 7;
	mPosY = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3.4;
	mSizeIcon.setPos(mPosX, mPosY);
	createDeck();
	EmptyDeck.setPos(mPosX, mPosY);
}
Opponent_Deck::Opponent_Deck(const std::shared_ptr<Opponent_Field> &field, const std::shared_ptr<Opponent_Hand> &hand)
{

	mField = field;
	mHand = hand;
	mPosX = SCREEN_WIDTH - SCREEN_WIDTH / 7;
	mPosY = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3.4;
	mSizeIcon.setPos(mPosX, mPosY);
	EmptyDeck.setPos(mPosX, mPosY);

}
Opponent_Deck::~Opponent_Deck()
{

}