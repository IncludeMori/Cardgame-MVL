#pragma once

#include <memory>
#include <iostream>

#include "MonsterCard.hpp"
#include "Resource.hpp"

#include "Place.hpp"
#include "Graveyard.hpp"

class Hand : public Place
{
public:
	Hand();
	~Hand();

	virtual void render();
	
	bool drawCard(std::shared_ptr<BaseCard> card);
	void startTurn();

	int getPosXFromCard(int index);
	int getPosYFromCard(int index);
	std::shared_ptr<BaseCard> getCard(int index);
	std::shared_ptr<BaseCard> getCardAt(int index);

	void setGraveyard(std::shared_ptr<Graveyard> grave);

	bool isUsingACard();

	void free();

protected:
	void rearrange(int index);
	void rearrangeRemove(int index);
	void rearrangeAdd();

	void updatePos();

	const int MAX_SIZE = 10;

	int mNextDrawIndex;
	bool mPlayable[10];

	Resource mResource;

	int mPosX[10], mPosY[10];
	int mShift[10];
	bool mCard_isActive[10]; 

	bool isMovingACard = false;
};