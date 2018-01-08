#include "ManageCardsC.hpp"

#include <iostream>

ManageCardsC::ManageCardsC()
{
	for (int i = 0; i < 7; i++)
		mCard[i] = nullptr;
}


ManageCardsC::~ManageCardsC()
{
}


void ManageCardsC::rearrange(int index)
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
	else if (mCard[index + 2] != nullptr && index + 2 < 7)
	{
		std::cout << "swap:" << index << " with" << index + 2 << std::endl;
		std::cout << "Current size:" << mSize - 1 << std::endl;
		mCard[index].swap(mCard[index + 2]);
		updatePos(index);
		mCard_isActive[index] = true;
		mCard_isActive[index + 2] = false;
		rearrange(index + 2);
	}
	else
		std::cout << "------------------------------------------------------------------------------------" << std::endl;

}

void ManageCardsC::updatePos(int index)
{
	std::cout << "Update Pos:" << index << std::endl;
	if (mCard[index] != nullptr)
		mCard[index]->setPos(mPosX[index], mPosY[index]);
}