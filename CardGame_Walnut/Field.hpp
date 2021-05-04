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

enum class CardPlace : bool
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

	std::shared_ptr<BaseCard> getCardAt(int index);

	virtual void render();
 
	void DmgCard(int index, int amount);
	virtual bool ChooseCard();

	void setGraveyard(std::shared_ptr<Graveyard> grave);

	bool hasSpace();
	int wantsToAttack();
	int getMouseAboveCard();

	bool isFull();

	void free();

protected:
	CardPlace mLastCardPlacedAt;
	bool mLastCardOverwritten = false; //wurde eine andere karte überschrieben, wird genutzt um dann trotzdem Feld zu fokusieren

	Field_HoverEffect mHoverEffectTexture;
	DefaultTexture mBackground;
	std::shared_ptr<EffectField> mEffectField; //shared between PlayerField && OpponentField

	Arrow mArrowAttackCard;
	Arrow mArrowAttackTarget;

	SDL_Rect mData;//field data

	const int MAX_SIZE = 7;

	int mActiveCard;
	int mFieldHasACard[7];

	//Card position
	//std::vector<int, int> mPosition;
	int mPosX[7];
	int mPosY[7];
	int mCardPosIndex[7] = { 3,0,1,2,4,5,6 };


	//void rearrange(int index); // -> removed card[index]
	//void updatePos(int index);

	void removeCard(int index);

	void updateFieldWithNewCard(int index);
	void updatePositions();

	void organizeField(); //

	int getFieldIndexFromCardAt(int index);

	void updatePosition(); //update card position


};