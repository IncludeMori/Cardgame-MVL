#pragma once

#include <memory>
#include <vector>

#include "Basic_Card.hpp"
#include "Default_Card.hpp"
#include "HeroHealth.hpp"

#include "Place.hpp"

class Deck
	: public Place, public std::enable_shared_from_this<Deck>
{
public:

	Deck();
	~Deck();
	
	void render();

	void setAlpha(Uint8 alpha);

	int getSize();
	std::shared_ptr<Basic_Card> getNextCard();
	std::shared_ptr<Basic_Card> CardAt(int index);

	void free();

	//
	virtual void createDeck();

protected:
	int mPosX, mPosY;

	const int MAX_SIZE = 30;
	const int MIN_SIZE = 20;
	const int MAX_SAME_CARD = 3;

	std::shared_ptr<Basic_Card> mEmptyCard = nullptr;
	std::vector<std::shared_ptr<Basic_Card>> mCard;
	std::vector<std::shared_ptr<Basic_Card>>::iterator mCardIt;
	DefaultTexture EmptyDeck;
	
	HeroHealth mSizeIcon;

	int mSize;
	int mCurrentTop;

	//pass to Default_Card 
	std::weak_ptr<Field> mField;
	std::weak_ptr<Hand> mHand;
	//Functions
	
};