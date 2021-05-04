#include "Deck.hpp"

#include "Load_Deck.hpp"

#include <iostream>

#include "Field.hpp"
#include "Hand.hpp"

Deck::Deck()
{
	mSize = 0;
	mCurrentTop = 0;
	mPosX = 0;
	mPosY = 0;
	mSizeIcon.changeDataTo(mSize);
	mSizeIcon.setPos(mPosX, mPosY);
	EmptyDeck.loadFromFile("Data/emptyDeck.png");
}
Deck::~Deck()
{

}

void Deck::render()
{
	if (mCurrentTop < MAX_SIZE) {
		mCard[mCurrentTop]->renderCardback();
		mSizeIcon.render();
	}
	else
		EmptyDeck.render();
}

void Deck::setAlpha(Uint8 alpha)
{
	for (unsigned int i = 0; i < mCard.size(); i++)
		mCard[i]->setAlpha(alpha);

}

int Deck::getSize()
{
	return mSize-mCurrentTop;
}

std::shared_ptr<BaseCard> Deck::getNextCard()
{
	if (mCurrentTop < MAX_SIZE)
	{
		mSizeIcon.changeDataTo(mSize-(mCurrentTop+1));
		std::cout << "Get Card from Deck. Index:" << mCurrentTop << std::endl;
		return mCard.at(mCurrentTop++);
	}
	else { return nullptr; }
}

std::shared_ptr<BaseCard> Deck::getCardAt(int index)
{
	if (index >= mCurrentTop)
		return mCard[index];
	else
		return nullptr;
}

//protected
void Deck::createDeck()
{
	std::string path = "test_card";

	for (int i = 0; i < MAX_SIZE; i++)
	{
		path = "test_boost_hand";
		mCard.push_back(std::shared_ptr<BaseCard>(new MonsterCard(path,1)));
		mCard[i]->setPos(mPosX, mPosY);

		if (mField.lock() != nullptr && mHand.lock() != nullptr)
		{
			mCard[i]->setStuff(shared_from_this(), mHand, mField,mField);
		}
		

		mSize++;
		std::cout << "DeckSize:" << mSize << std::endl;
	}

	for (int i = 0; i < MAX_SIZE; i++)
	{
		std::dynamic_pointer_cast<MonsterCard>(mCard[i])->loadTexture();
	}

	mSizeIcon.changeDataTo(mSize);
}

void Deck::free()
{
	
}