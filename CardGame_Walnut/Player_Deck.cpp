#include "Player_Deck.hpp"

#include <iostream>
#include "gScreenSize.hpp"

#include "Player_Field.hpp"
#include "Player_Hand.hpp"

#include "Load_Deck.hpp"
#include "Effect_Card.hpp"

#include <algorithm>
#include <memory>

using std::dynamic_pointer_cast;

Player_Deck::Player_Deck()
{
	mPosX = SCREEN_WIDTH - SCREEN_WIDTH / 7;
	mPosY = SCREEN_HEIGHT - SCREEN_HEIGHT / 2.3 -60;
	

	mSizeIcon.setPos(mPosX, mPosY);
	EmptyDeck.setPos(mPosX, mPosY);

}
Player_Deck::Player_Deck(const std::shared_ptr<Player_Field> &field, const std::shared_ptr<Player_Hand> &hand)
{
	mField = field;
	mHand = hand;

	mPosX = SCREEN_WIDTH - SCREEN_WIDTH / 7;
	mPosY = SCREEN_HEIGHT - SCREEN_HEIGHT / 2.3 -30;


	mSizeIcon.setPos(mPosX, mPosY);
	EmptyDeck.setPos(mPosX, mPosY);

}

void Player_Deck::createDeck(const std::shared_ptr<Opponent_Field>&field)
{
	std::string path = "test_card";

	std::vector<std::string> deck;

	Load_Deck lD;

	//---------------
	deck = lD.loadDeck();
	std::random_shuffle(deck.begin(), deck.end());

	for (unsigned int i = 0; i <deck.size(); i++)
	{
		std::string y = deck.at(i).substr(1, deck.at(i).size());

		if (deck.at(i).at(0) == 'm')
		{

	
			mCard.push_back(std::shared_ptr<Basic_Card>(new Default_Card(y, 1)));
			mCard[i]->setPos(mPosX, mPosY);

		}
		else if (deck.at(i).at(0) == 'e')
		{

			mCard.push_back(std::shared_ptr<Basic_Card>(new Effect_Card(y)));
			mCard[i]->setPos(mPosX, mPosY);

		}
		else
			__debugbreak();


	
		mCard[i]->setStuff(shared_from_this(), mHand, mField,field);
		mCard[i]->changePosition(Position::DECK);
	
		mSize++;
		std::cout << "DeckSize:" << mSize << std::endl;

	//deck += path;
	//deck += "0";
	}


	
	// load card_texture
	for (unsigned int i = 0; i < mCard.size(); i++)
	{
		if (deck.at(i).at(0) == 'm') dynamic_pointer_cast<Default_Card>(mCard[i])->loadTexture();
	}
	//-----------------------------------------
	/*
	deck = lD.loadMonster();
	std::random_shuffle(deck.begin(), deck.end());
	
	for (int i = 0; i <deck.size(); i++)
	{
		mCard.push_back(std::shared_ptr<Basic_Card>(new Default_Card(deck.at(i), 1)));
		mCard[i]->setPos(mPosX, mPosY);

		if (mField != nullptr && mHand != nullptr)
		{
			if (field == nullptr)
				__debugbreak();
			mCard[i]->setStuff(shared_from_this(), mHand, mField,field);
			
			mCard[i]->changePosition(Position::DECK);
		}


		mSize++;
		std::cout << "DeckSize:" << mSize << std::endl;

		//deck += path;
		//deck += "0";
	}
	// load card_texture
	for (int i = 0; i < mCard.size(); i++)
	{
		dynamic_pointer_cast<Default_Card>(mCard[i])->loadTexture();
	}

	
	deck = lD.loadZauber();
	

	for (int i = 0; i < deck.size(); i++)
	{
		mCard.push_back(std::shared_ptr<Basic_Card>(new Effect_Card(deck.at(i))));

		mCard[mCard.size() - 1]->setPos(mPosX, mPosY);

		if (mField != nullptr && mHand != nullptr)
		{
			mCard[mCard.size() - 1]->setStuff(shared_from_this(), mHand, mField,field);
			mCard[mCard.size() - 1]->changePosition(Position::DECK);
		}

		
		mSize++;
		std::cout << "DeckSize:" << mSize << std::endl;

		//deck += path;
		//deck += "0";
	}
	*/
	mSizeIcon.changeDataTo(mSize);
}

Player_Deck::~Player_Deck()
{
	free();
}
