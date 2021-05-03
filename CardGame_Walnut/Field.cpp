#include "Field.hpp"

#include <iostream>

#include "Card_Effects.hpp"
#include "gMouse.hpp"
#include "Arrow.hpp"
#include "Click_EventHandler.hpp"

#include "gScreenSize.hpp"

#include <boost/range/irange.hpp>


using namespace boost;

Field::Field()
{
	mSize = 0;
	mActiveCard = -1;

	mAttackCard.loadFromFile("Data/pfeil_attack.png");
	mAttackTarget.loadFromFile("Data/target_attack.png");

	mBackground.loadFromFile("Data/Field/field_background.png");
	mBackground.setPos(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 4);
}
Field::~Field()
{

}

void Field::render()
{
	mBackground.render();
	mHoverEffectTexture.render();
	//std::shared_ptr<BaseCard> card(new MonsterCard());
    //std::dynamic_pointer_cast<MonsterCard>(card)->
	
	int hover = -1;
	bool hoverIsActive = false;
	

	drawRect(mData);

	for (int i = 0; i < 7; i++)
	{
		if (mCard[i] != nullptr) { mCard[i]->render(hoverIsActive);}

		if (hoverIsActive)
		{
			hover = i;
			hoverIsActive = false;
		}
	}

	if (mAttackCard.isActive()) { mAttackCard.render(); }
	if (mAttackTarget.isActive()) { mAttackTarget.render(); }

	if (hover != -1)
		mCard[hover]->renderHoverEffect();


}

void Field::addCard(const std::shared_ptr<BaseCard>& card)
{
	if (card == nullptr) {  }
	else
	{
		mSize++;
		mCard[mSize - 1] = card;
		mFieldHasACard[mSize - 1] = true;
		std::dynamic_pointer_cast<MonsterCard>(mCard[mSize - 1])->changePlacePosition(Position::FIELD);
		mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
		if (std::dynamic_pointer_cast<MonsterCard>(mCard[mSize - 1])->getEffect() == eEffect::BATTLECRY)
			mCard[mSize-1]->activateEffect();
		
	}	    
}

void Field::addCard(const std::shared_ptr<BaseCard>& card, int posX, int posY)
{
	
	if (card == nullptr) { __debugbreak(); }
	else
	{
		if (mSize == 0)
		{
			mSize++;
			mCard[mSize - 1] = card;
			mFieldHasACard[mSize - 1] = true;
			std::dynamic_pointer_cast<MonsterCard>(mCard[mSize - 1])->changePlacePosition(Position::FIELD);
			mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
			if (std::dynamic_pointer_cast<MonsterCard>(mCard[mSize - 1])->getEffect() == eEffect::BATTLECRY)
				mCard[mSize - 1]->activateEffect();
		}
		else
		{
			//---------------------------------------------
			// LEFT SIDE
			if (posX < mPosX[0] && mSize < 7)
			{
				// 2 4 6
				if (posX < mPosX[4])
				{

				}
				else if (posX < mPosX[2])
				{

				}
				else
				{

				}
			//----------------------------------------------
			// RIGHT SIDE
			}
			else if (posX > mPosX[0] && mSize < 7)
			{
				// 1 3 5
				if (posX > mPosX[3])
				{

				}
				else if (posX > mPosX[1])
				{

				}
				else
				{

				}
			}
			//------------------------------------------------
			//error
			else
				__debugbreak();
		}


	}
	
}

void Field::addCard(const std::shared_ptr<BaseCard>& card, int index)
{
	//todo
}

std::shared_ptr<BaseCard> Field::CardAt(int index)
{
	return mCard[index];
}

void Field::DmgCard(int index, int amount)
{
	std::cout << "Index:" << index << ",Dmg:" << amount << std::endl;
	std::dynamic_pointer_cast<MonsterCard>(mCard[index])->removeHealth(amount);
	if (!std::dynamic_pointer_cast<MonsterCard>(mCard[index])->isAlive()) {
		std::dynamic_pointer_cast<MonsterCard>(mCard[index])->changePlacePosition(Position::DEAD);
		mGraveyard->add(mCard[index]);
		if (std::dynamic_pointer_cast<MonsterCard>(mCard[index])->getEffect() == eEffect::DEATHWISH)
		{
			mCard[index]->activateEffect();
		}
		//rearrange(index); mSize--;
	}
}

bool Field::ChooseCard()
{
	return false;
}

void Field::setGraveyard(std::shared_ptr<Graveyard> grave)
{
	mGraveyard = grave;
}

int Field::getSize()
{
	return mSize;
}
bool Field::hasSpace()
{
	if (mSize < MAX_SIZE) { return true; }
	else return false;
}
int Field::wantsToAttack()
{
	return mActiveCard;
}

//protected
void Field::updatePosition()
{

}

int Field::getMouseAboveCard()
{
	
	for (int i = 0; i < 7; i++)
	{
		if (mCard[i] != nullptr) {
			if (mCard[i]->mouseIsAbove())
			{

				return i;
			}
		}
		else {}
	}

	//else
	
	return -1;
}

bool Field::isFull()
{
	if (mSize >= MAX_SIZE)
	{
		return true;
	}
	else return false;
}
/*
void Field::rearrange(int index)
{
	//Field setup    0 1
	//warning?
	if (index == 0 && mCard[index + 1] != nullptr)
	{
		std::cout << "swap:" << index << " with" << index + 1 << std::endl;
		std::cout << "Current size:" << mSize - 1 << std::endl;
		mCard[index].swap(mCard[index + 1]);
		updatePos(index);
		mCard_isActive[index] = true;
		mCard_isActive[index + 1] = false;
		rearrange(index + 1);
	}
	else if (mCard[index+2] != nullptr && index+2 < 7)
	{
		std::cout << "swap:" << index << " with" << index + 2 << std::endl;
		std::cout << "Current size:" << mSize-1 << std::endl;
		mCard[index].swap(mCard[index + 2]);
		updatePos(index);
		mCard_isActive[index] = true;
		mCard_isActive[index + 2] = false;
		rearrange(index + 2);
	}
	else
		std::cout << "------------------------------------------------------------------------------------" << std::endl;
	
}*/
/*
void Field::updatePos(int index)
{
	/*
	std::cout << "Update Pos:" << index << std::endl;
	if (mCard[index] != nullptr) 
		mCard[index]->setPos(mPosX[index], mPosY[index]);
}*/

void Field::free()
{
	
	for (int i = 0; i < 7; i++)
		mCard[i] = nullptr;
}




void Field::removeCard(int index)
{
	mCard[index].reset();
	mCard[index] = nullptr;

	int card_pos = mCardPosIndex[index];
	mCardPosIndex[index] = mSize;
	std::cout << "removed card pos:" << card_pos << std::endl;
	
	if (mSize % 2 == 0)
	{

		for (int i = 0; i < MAX_SIZE; i++)
			if (mCardPosIndex[i] > card_pos)
				if (mCard[i] != nullptr)
					mCardPosIndex[i]--;
	}
	else
	{
		for (int i = 0; i < MAX_SIZE; i++)
			if (mCardPosIndex[i] < card_pos)
				if (mCard[i] != nullptr)
					mCardPosIndex[i]++;
	}
	mSize--;
	updatePositions();
}

void Field::updateFieldWithNewCard(int index)
{
	//index = 1
	// 1 should go to 2
	// 0 should stay at 0
	//all move to 1???
	for (int i : irange(0, mSize))
		if (mCardPosIndex[i] >= index)
			mCardPosIndex[i]++;
	mCardPosIndex[mSize] = index;

	if (index > 3 && mSize % 2 != 1)
	{
		last_added = Last_Added::RIGHT;
		mLastCardOverwritten = true;
	}
	else if (index < 4 && mSize % 2 != 1)
	{
		last_added = Last_Added::LEFT;
		mLastCardOverwritten = true;
	}

	updatePositions();

}

void Field::updatePositions()
{
	if (mSize >= 1)
		for (int i : irange(0, MAX_SIZE))
			if (mCard[i] != nullptr)
			{
				mCard[i]->setPos(mPosX[mCardPosIndex[i]], mPosY[mCardPosIndex[i]]);

				std::cout << "Card@" << i << " set to index" << mCardPosIndex[i] << std::endl;
			}
}

void Field::organizeField()
{
	if (last_added == Last_Added::LEFT)
	{
		if ((mSize - 1) % 2 == 1 && mLastCardOverwritten == false)
		{
			for (int i : irange(0, MAX_SIZE))
				mCardPosIndex[i]++;
		}
		else if (mLastCardOverwritten == true)
			for (int i : irange(0, MAX_SIZE))
				mCardPosIndex[i]--;

	}
	else
	{
		if (mSize % 2 == 1 || mLastCardOverwritten == true)
			for (int i : irange(0, MAX_SIZE))
				mCardPosIndex[i]--;
	}
	mLastCardOverwritten = false;

	
}

int Field::getCardAt(int index)
{

	for (int i = 0; i<MAX_SIZE; i++)
	{
		if (mCardPosIndex[i] == index)
			return i;
	}
	return 6;
}