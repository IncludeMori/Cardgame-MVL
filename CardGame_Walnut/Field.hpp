#pragma once

#include <memory>

#include "BaseCard.hpp"
#include "MonsterCard.hpp"
#include "draw.hpp" //dev test function
#include "Arrow.hpp"
#include "ManageCardsC.hpp"
#include "Place.hpp"

#include "EffectField.hpp"

#include "Graveyard.hpp"

#include "Field_HoverEffect.hpp"

enum class Last_Added : bool
{
	LEFT = true,
	RIGHT = false
};

class Field : public Place
{
public:
	Field();
	~Field();
	
	virtual void addCard(const std::shared_ptr<BaseCard>& card);
	virtual void addCard(const std::shared_ptr<BaseCard>& card, int posX,int posY); //TODO
	virtual void addCard(const std::shared_ptr<BaseCard>& card, int index);

	virtual void addEffectCard(const std::shared_ptr<BaseCard> &card) {};

	std::shared_ptr<BaseCard> CardAt(int index);

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
	Last_Added last_added;
	bool mLastCardOverwritten = false; //wurde eine andere karte überschrieben, wird genutzt um dann trotzdem feld zu fokusieren

	Field_HoverEffect mHoverEffectTexture;
	DefaultTexture mBackground;
	std::shared_ptr<EffectField> mEffectField; //shared between PlayerField && OpponentField

	//void rearrange(int index); // -> removed card[index]
	//void updatePos(int index);

	void removeCard(int index);

	void updateFieldWithNewCard(int index);
	void updatePositions();

	void organizeField(); //

	int getCardAt(int index);

	Arrow mAttackCard;
	Arrow mAttackTarget;

	void updatePosition(); //update card position

	SDL_Rect mData;//field data
	
	const int MAX_SIZE = 7;
	int mSize;
	int mActiveCard; 
	int mFieldHasACard[7];

	//pointer to [Deck]
	std::shared_ptr<BaseCard> mCard[7];

	//Card position
	//std::vector<int, int> mPosition;
	int mPosX[7];
	int mPosY[7];
	int mCardPosIndex[7] = { 3,0,1,2,4,5,6 };

	std::shared_ptr<Graveyard> mGraveyard;
};