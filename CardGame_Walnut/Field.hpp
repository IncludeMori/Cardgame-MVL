#pragma once

#include <memory>

#include "Basic_Card.hpp"
#include "Default_Card.hpp"
#include "draw.hpp" //dev function
#include "Arrow.hpp"
#include "ManageCardsC.hpp"
#include "Place.hpp"

#include "EffectField.hpp"

#include "Graveyard.hpp"

class Field : public Place
{
public:
	Field();
	~Field();
	
	virtual void addCard(const std::shared_ptr<Basic_Card>& card);
	virtual void addCard(const std::shared_ptr<Basic_Card>& card, int posX,int posY); //not done yet

	virtual void addEffectCard(const std::shared_ptr<Basic_Card> &card) {};

	std::shared_ptr<Basic_Card> CardAt(int index);

	virtual void render();
 
	void DmgCard(int index, int amount);
	virtual bool ChooseCard();

	void setGraveyard(std::shared_ptr<Graveyard> grave);

	int getSize();
	bool hasSpace();
	int wantsToAttack();
	int getMouseAboveCard();

	bool isFull();

	void free();

protected:
	DefaultTexture mBackground;
	std::shared_ptr<EffectField> mEffectField; //shared between PlayerField && OpponentField

	void rearrange(int index); // -> removed card[index]
	void updatePos(int index);

	Arrow mAttackCard;
	Arrow mAttackTarget;

	void updatePosition(); //update card position

	SDL_Rect mData;//field data
	
	const int MAX_SIZE = 7;
	int mSize;
	int mCardIsActive;
	int mCard_isActive[7];

	//pointer to [Deck]
	std::shared_ptr<Basic_Card> mCard[7];

	//Card position
	//std::vector<int, int> mPosition;
	int mPosX[7];
	int mPosY[7];
	int mCardPosIndex[7] = { 3,0,1,2,4,5,6 };

	std::shared_ptr<Graveyard> mGraveyard;
};