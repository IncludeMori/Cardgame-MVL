#include "Hand.hpp"

Hand::Hand()
{
	for (int i = 0; i < MAX_SIZE; i++)
		mShift[i] = 5;
	mNextDrawIndex = 4;
}
Hand::~Hand()
{
	free();
}

void Hand::render()
{
	mResource.render();
	for (int i = 0; i < mSize; i++)
	{
		if (mCard[i] != nullptr) { mCard[i]->render(); }
		else __debugbreak();
	}

}

bool Hand::drawCard(std::shared_ptr<BaseCard> card)
{
	if (card != nullptr)
	{
		if (mSize < MAX_SIZE)
		{

			mSize++;
			mCard[mSize-1] = card;
			mCard[mSize - 1]->changePlacePosition(Position::HAND);
			mCard[mSize - 1]->setPos(mPosX[mSize - 1+(mShift[mSize-1])], mPosY[mSize - 1+(mShift[mSize-1])]);
			mPlayable[mSize - 1] = true;
			mCard_isActive[mSize - 1] = true;

			rearrangeAdd();
			updatePos();

			return true;
		}
		else
		{
			mGraveyard->add(card);
			return true;
		}
	}
	else
	{
		return false;
	}
}

void Hand::startTurn()
{
	mResource.increase();
}

std::shared_ptr<BaseCard> Hand::getCard(int index)
{
	mCard_isActive[index] = false;
	std::shared_ptr<BaseCard> x;
	x.swap(mCard[index]);
	rearrangeRemove(index);
	mSize--;
	updatePos();

	std::cout << "Return Card:" << index << std::endl;

	return x;
}

std::shared_ptr<BaseCard> Hand::CardAt(int index)
{
	return mCard[index];
}

void Hand::setGraveyard(std::shared_ptr<Graveyard> grave)
{
	mGraveyard = grave;
}

int Hand::getPosX(int index)
{
	return mCard[index]->getPosX();
}
int Hand::getPosY(int index)
{
	return mCard[index]->getPosY();
}
int Hand::getSize()
{
	return mSize;
}

bool Hand::isUsingACard()
{
	return isMovingACard;
}

void Hand::rearrange(int index)
{
	/*//DRAW-> card @ mSize

	std::cout << std::endl;
	std::cout << "current Hand before:" << std::endl;
	for (int i = 0; i < 6; i++)
		if (mCard[i] == nullptr) std::cout << "0"; else std::cout << "-";
    std::cout << std::endl;



	if (index == 0 && index+1 < mSize)
	{
		mCard[index].swap(mCard[index + 1]);
		std::cout << "swap : " << index + 1 << "<->" << index << std::endl;

		updatePos(index);
		mCard_isActive[index] = true;
		mCard_isActive[index + 1] = false;
		rearrange(index + 1);
	}
	else if (index+2<MAX_SIZE)
	{
		mCard[index].swap(mCard[index + 2]);
		std::cout << "swap : " << index + 2 << "<->" << index << std::endl;
		for (int i = 0; i < 6; i++)
			if (mCard[i] == nullptr) std::cout << "0"; else std::cout << "-";
		updatePos(index);
		mCard_isActive[index] = true;
		mCard_isActive[index + 2] = false;
		rearrange(index + 2);
	}
	



	if (index + 2 == mSize - 2){
		mCard[index + 2].swap(mCard[mSize - 1]);
		std::cout << "swap : " << index + 2 << "->" << mSize-1 << std::endl;
		updatePos(index + 2);
	}

	for (int j=0;j<5;j++)
	for (int i = 0; i < 5; i++)
		if (mCard[i] == nullptr && mCard[i + 1] != nullptr)
			mCard[i].swap(mCard[i + 1]);  */
}

void Hand::rearrangeRemove(int index) //removed card@index
{
	//KARTE ENTFERN (index)
	//if index <= 4, alle kleiner als index einen nach Rechts verschieben
	//if index >= 5 alle größer als index einen nach Links verschieben
	mPlayable[mSize-1] = false;
	mCard_isActive[mSize-1] = false;

	mPlayable[index] = true;
	mCard_isActive[index] = true;

	for (int i = index; i < mSize-1; i++)
	{
		mCard[i].swap(mCard[i + 1]);
	}

	if (mSize % 2 == 1)
	{
		for (int i = 0; i < MAX_SIZE; i++)
			mShift[i] = mShift[i];
	}
	else
	{
		for (int i = 0; i < MAX_SIZE; i++)
			mShift[i] = mShift[i]+1;
	}
}

void Hand::rearrangeAdd()
{
	if ((mSize-1) % 2 == 1)
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			mShift[i] = mShift[i] - 1;
		}
	}
}

void Hand::updatePos()
{
	for (int index = 0;index<MAX_SIZE;index++)
		if (mCard[index] != nullptr)
		{
			mCard[index]->setPos(mPosX[index + mShift[index]], mPosY[index + mShift[index]]);
		}
}

void Hand::free()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		mCard[i] = nullptr;
	}

}