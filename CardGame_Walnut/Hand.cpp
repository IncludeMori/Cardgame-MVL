#include "Hand.hpp"

Hand::Hand()
{

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
		//else //__debugbreak();
	}

}

bool Hand::drawCard(std::shared_ptr<Basic_Card> card)
{
	if (card != nullptr)
	{
		if (mSize < MAX_SIZE)
		{
			mSize++;
			mCard[mSize - 1] = card;
			mCard[mSize - 1]->changePosition(Position::HAND);
			mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
			mPlayable[mSize - 1] = true;
			mCard_isActive[mSize - 1] = true;
			std::cout << "Added Card at index:" << mSize - 1 << std::endl;
			std::cout << "Set Pos: X:" << mPosX[mSize - 1] << "  Y:" << mPosY[mSize - 1] << std::endl;
			return true;

		}
		else
			mGraveyard->add(card);
	}
	else
		return false;

}

void Hand::startTurn()
{
	mResource.increase();
}

std::shared_ptr<Basic_Card> Hand::getCard(int index)
{
	mCard_isActive[index] = false;
	std::shared_ptr<Basic_Card> x;
	x.swap(mCard[index]);
	std::cout << "Return Card:" << index << std::endl;
	//mCard[index] = nullptr;
	std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
	rearrange(index);
	std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;
	std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;
	mSize--;
	
	std::cout << "current Hand afterwards:" << std::endl;
	for (int i = 0; i < 6; i++)
		if (mCard[i] == nullptr) std::cout << "0"; else std::cout << "-";
	std::cout << "Removed::" << mSize << std::endl;

	std::cout << std::endl;
	std::cout << "mSize:" << mSize << std::endl;

	return x;
}

std::shared_ptr<Basic_Card> Hand::CardAt(int index)
{
	return mCard[index];
}

void Hand::setGraveyard(std::shared_ptr<Graveyard> grave)
{
	mGraveyard = grave;
}

int Hand::getPosX(int index)
{
	return mCard[index]->getX();
}
int Hand::getPosY(int index)
{
	return mCard[index]->getY();
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
	//Field setup    0 1
	//warning?
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
			mCard[i].swap(mCard[i + 1]);
}

void Hand::updatePos(int index)
{
	if (mCard[index] != nullptr)
		mCard[index]->setPos(mPosX[index], mPosY[index]);
}
void Hand::free()
{
	mResource.free();

	for (int i = 0; i < MAX_SIZE; i++)
	{
		mCard[i] = nullptr;
	}

}