#include "Graveyard.hpp"

#include "gScreenSize.hpp"
#include "gScreenSize.hpp"

Graveyard::Graveyard()
{
	mCurrentSize = 0;
	mPosX = SCREEN_WIDTH - SCREEN_WIDTH / 7;
	mIsActive = false;
	mPosY = 5;

	mEmptyGraveTexture.loadFromFile("Data/emptyDeck.png");
	mEmptyGraveTexture.setPos(mPosX, mPosY);
}
Graveyard::Graveyard(int who)
{
	mCurrentSize = 0;
	mPosX = 50;
	mIsActive = false;


	if (who == 0)
	{
		mPosY = SCREEN_HEIGHT - 70;
	}
	else
	{
		mPosY = 100;
	}

	mEmptyGraveTexture.loadFromFile("Data/emptyDeck.png");
	mEmptyGraveTexture.setPos(mPosX, mPosY);
}




Graveyard::~Graveyard()
{
	free();
}

void Graveyard::render()
{
	if (mCurrentSize == 0)
		mEmptyGraveTexture.render();
	else
		mCards[mCurrentSize-1]->render();
}

void Graveyard::add(std::shared_ptr<Basic_Card> card)
{
	card->setPos(mPosX, mPosY);
	mCards[mCurrentSize] = card;
	mCurrentSize++;
}

std::shared_ptr<Basic_Card> Graveyard::get(int index)
{
	if (index < mCurrentSize)
		return mCards[index];
	else
		return nullptr;
}

void Graveyard::show()
{
}

bool Graveyard::ShowIsActive()
{
	return mIsActive;
}

void Graveyard::init(int who)
{
	if (who == 0)
	{
		mPosY = SCREEN_HEIGHT -250;
	}
	else
	{
		mPosY = 100;
	}
	mEmptyGraveTexture.setPos(mPosX, mPosY);
}

void Graveyard::free()
{
	
}
