#pragma once

#include "BaseCard.hpp"


class ManageCardsC
{
public:
	ManageCardsC();
	~ManageCardsC();


	void rearrange(int index); // -> removed card[index]
	void updatePos(int index);

	
	std::shared_ptr<BaseCard> mCard[7];
	int mPosX[7];
	int mPosY[7];

	const int mMax_Size = 7;
	int mSize;
	int mCardIsActive;
	int mCard_isActive[7];
	
};

