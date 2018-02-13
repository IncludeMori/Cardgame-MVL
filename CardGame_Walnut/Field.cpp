#include "Field.hpp"

#include <iostream>

#include "Card_Effects.hpp"
#include "gMouse.hpp"
#include "Arrow.hpp"
#include "Click_EventHandler.hpp"
#include "gRenderer.hpp"
#include "gScreenSize.hpp"

Field::Field()
{
	mSize = 0;
	mCardIsActive = -1;

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
	//std::shared_ptr<Basic_Card> card(new Default_Card());
    //std::dynamic_pointer_cast<Default_Card>(card)->
	
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

void Field::addCard(const std::shared_ptr<Basic_Card>& card)
{
	if (card == nullptr) {  }
	else
	{
		mSize++;
		mCard[mSize - 1] = card;
		mCard_isActive[mSize - 1] = true;
		std::dynamic_pointer_cast<Default_Card>(mCard[mSize - 1])->changePosition(Position::FIELD);
		mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
		if (std::dynamic_pointer_cast<Default_Card>(mCard[mSize - 1])->getEffect() == eEffect::BATTLECRY)
			mCard[mSize-1]->activateEffect();
		
	}	    
}

void Field::addCard(const std::shared_ptr<Basic_Card>& card, int posX, int posY)
{
	
	if (card == nullptr) { __debugbreak(); }
	else
	{
		if (mSize == 0)
		{
			mSize++;
			mCard[mSize - 1] = card;
			mCard_isActive[mSize - 1] = true;
			std::dynamic_pointer_cast<Default_Card>(mCard[mSize - 1])->changePosition(Position::FIELD);
			mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
			if (std::dynamic_pointer_cast<Default_Card>(mCard[mSize - 1])->getEffect() == eEffect::BATTLECRY)
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

std::shared_ptr<Basic_Card> Field::CardAt(int index)
{
	return mCard[index];
}

void Field::DmgCard(int index, int amount)
{
	std::cout << "Index:" << index << ",Dmg:" << amount << std::endl;
	std::dynamic_pointer_cast<Default_Card>(mCard[index])->removeHealth(amount);
	if (!std::dynamic_pointer_cast<Default_Card>(mCard[index])->isAlive()) {
		std::dynamic_pointer_cast<Default_Card>(mCard[index])->changePosition(Position::DEAD);
		mGraveyard->add(mCard[index]);
		if (std::dynamic_pointer_cast<Default_Card>(mCard[index])->getEffect() == eEffect::DEATHWISH)
		{
			mCard[index]->activateEffect();
		}
		rearrange(index); mSize--; }
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
	if (mSize < mMax_Size) { return true; }
	else return false;
}
int Field::wantsToAttack()
{
	return mCardIsActive;
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
			if (mCard[i]->MouseIsAbove())
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
	if (mSize >= mMax_Size)
	{
		return true;
	}
	else return false;
}

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
	
}

void Field::updatePos(int index)
{
	std::cout << "Update Pos:" << index << std::endl;
	if (mCard[index] != nullptr) 
		mCard[index]->setPos(mPosX[index], mPosY[index]);
}

void Field::free()
{
	mAttackTarget.free();
	mAttackCard.free();

	for (int i = 0; i < 7; i++)
		mCard[i] = nullptr;
}