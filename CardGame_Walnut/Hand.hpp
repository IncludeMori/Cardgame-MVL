#pragma once

#include <memory>
#include <iostream>

#include "Default_Card.hpp"
#include "Resource.hpp"

#include "Place.hpp"
#include "Graveyard.hpp"

class Hand : public Place
{
public:
	Hand();
	~Hand();

	virtual void render();
	
	bool drawCard(std::shared_ptr<Basic_Card> card);
	void startTurn();

	int getSize();
	int getPosX(int index);
	int getPosY(int index);
	std::shared_ptr<Basic_Card> getCard(int index);
	std::shared_ptr<Basic_Card> CardAt(int index);

	void setGraveyard(std::shared_ptr<Graveyard> grave);

	bool isUsingACard();

	void free();

protected:
	void rearrange(int index);
	void updatePos(int index);

	//check if I need everything for OPP_HAND
	const int MAX_SIZE = 6;
	int mSize; //current handsize
	bool mPlayable[6];

	std::shared_ptr<Basic_Card> mCard[6];
	Resource mResource;

	int mPosX[6], mPosY[6];
	bool mCard_isActive[6]; // Spieler hat die Karte in der Hand

	bool isMovingACard = false;

	std::shared_ptr<Graveyard> mGraveyard;

};