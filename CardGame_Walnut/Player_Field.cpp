#include "Player_Field.hpp"

#include "gScreenSize.hpp"
#include "gMouse.hpp"
#include <iostream>
#include <boost/range/irange.hpp>

#include <memory>

using std::dynamic_pointer_cast;

using namespace boost;

Player_Field::Player_Field()
{
	//mHoverEffectTexture.loadFromFile("Data/place_card.png");

	TargetCard.loadFromFile("Data/target.png");
	TargetCard.setInactive();

	misUsingACard = false;
	mSize = 0;

	//Field data
	mData.x = 50;
	mData.y = SCREEN_HEIGHT / 2;
	mData.w = SCREEN_WIDTH-2*mData.x;
	mData.h = SCREEN_HEIGHT / 4;
	

	// Init Card X&Y pos     
	int x = SCREEN_WIDTH / 2 - 165 / 2;
	int y = SCREEN_HEIGHT - SCREEN_HEIGHT / 2 + 10;
	int change = 185;
	x = x - 3 * change;
	/*
	int x2 = SCREEN_WIDTH / 2 - 165 / 2;
	
	int y = SCREEN_HEIGHT -SCREEN_HEIGHT/ 2+10;
	int change = 185;
	const int Legion = change;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		mPosY[i] = y;
		mPosX[i] = x;
		x += change;
		if (change > 0) { change = (change + Legion) *-1; }
		else { change = (change + (Legion*-1))*-1; }
	}
	
	//....
	mPosY[0] = mPosY[1];*/

	for (int i : irange(0,MAX_SIZE))
	{
		mPosX[i] = x;
		mPosY[i] = y;
		x += change;
		mCard[i] = nullptr;
	}


	mBackground.setPos(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 2*(SCREEN_HEIGHT/4));
	
}
Player_Field::~Player_Field()
{

}

void Player_Field::addCard(const std::shared_ptr<BaseCard>& card)
{

	int posX = card->getPosX();
	int posY = card->getPosY();
	int index = -1;
	
	//find pos
	
	//search for index -> player wants to add card@index
	if (mSize == 0)
	{
		mCardPosIndex[0] = 3;
		index = 3;
	}
	else
	for (int i : irange(0,MAX_SIZE))
	{
		if (posX > mPosX[i] && posX < mPosX[i] + 200)
			index = i;
	}
	
	if (index != -1 && mSize >= 1 && card != nullptr)
		if (mCard[getFieldIndexFromCardAt(index)] == nullptr)
		{
			//außerhalb der gespielten Karten
			if (index > 3)
			{
				//index von rechster karte,
				//dann die neue Karte einen weiter rechts hinzufügen und dann eventuell alle karten einpendeln

				//rechteste karte finden
				int rechtesteKarte = -1;
				for (int i : irange(0, MAX_SIZE))
					if (mCardPosIndex[i] >= 4)
						if (mCard[i] != nullptr)
							if (mCardPosIndex[i] > rechtesteKarte)
								rechtesteKarte = mCardPosIndex[i];


				index = rechtesteKarte+1;
				if (rechtesteKarte == -1)
					index = 4;

				mLastCardPlacedAt = CardPlace::RIGHT;
			}
			else
			{
				//index von linkster karte

				//linkste karte finden
				int linksteKarte = 4;
				for (int i : irange(0, MAX_SIZE))
					if (mCardPosIndex[i] <= 3)
						if (mCard[i] != nullptr)
						{
							if (mCardPosIndex[i] < linksteKarte)
							{
								linksteKarte = mCardPosIndex[i];
								
							}
						}

				index = linksteKarte-1;
				if (linksteKarte == 3)
					index = 2;

		
				mLastCardPlacedAt = CardPlace::LEFT;

			}

			mCardPosIndex[mSize] = index;
			updatePositions();
		}
		else
			updateFieldWithNewCard(index);
	

	
	if (card == nullptr) {}
	else
	{
		

		mSize++;
		std::cout << "Index:" << mSize - 1 << std::endl;
		mCard[mSize - 1] = card;
		mCard[mSize - 1]->changePlacePosition(Position::FIELD);
		mFieldHasACard[mSize - 1] = true;
		mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
		if (dynamic_pointer_cast<MonsterCard>(mCard[mSize - 1])->getEffect() == eEffect::BATTLECRY)
		{
			if (mCard[mSize - 1]->activateEffect() == false)
			{
				battlecry_active = true;
				ba_card = mSize - 1;
				TargetCard.setActive();
				TargetCard.setPos(gMouse.getX()-TargetCard.getWidth()/2, gMouse.getY()-TargetCard.getHeight()/2);
			}
		}
		if (mSize>1)
		organizeField();
	}
	
	updatePositions();

	Dev_printCardPosIndex();

}
void Player_Field::addEffectCard(const std::shared_ptr<BaseCard>& card)
{
	if (card == nullptr) {}
	else
	{
		if (!Effect_Field.add(card))
		{
			std::cout << "Effect active" << std::endl;
				battlecry_active = true;
				TargetCard.setActive();
				TargetCard.setPos(gMouse.getX() - TargetCard.getWidth() / 2, gMouse.getY() - TargetCard.getHeight() / 2);
		}
	}

}

	

bool Player_Field::update()
{
	bool hoverIsActive = false;
	hover = -1;
	for (int i = 0; i < 7; i++)
	{
		if (mCard[i] != nullptr) {
			if (mFieldHasACard[i])
			{
				mCard[i]->setHover(hoverIsActive);
				if (hoverIsActive)
				{
					hover = i;
					hoverIsActive = false;
				}
			}

		}
	}
	/*
	int card = 0; //...

	for (int i = 0; i < mSize; i++)
	{
		if (mCard[i] != nullptr) {
			//check if player wants to use card
			if (gMouse.getState() && mCard[i]->mouseIsAbove() && !misUsingACard)
			{
				mCardIsActive = i;
				misUsingACard = true; // can only use one card at a time
			}

			//check if player is using a card
			/*
			if (mCard_isActive[i])
			{
				card = mOField->getMouseAboveCard();
				std::cout << "Index" << card << std::endl;
				if (card < 0)
				{
					//if "player" isnt targeting a enemy card, move AttackArrow back to active mCard
					mAttackArrow.setPos(mCard[i]->getX() + mCard[i]->getWidth() / 4, mCard[i]->getY() + mCard[i]->getHeight() / 4);
				}
				else
				{
					if (mOField->getCardAt(card) != nullptr)
					{
						mAttackArrow.setPos(mOField->getCardAt(card)->getX() + mOField->getCardAt(card)->getWidth() / 4,
							mOField->getCardAt(card)->getY() + mOField->getCardAt(card)->getHeight() / 4);
					}
					if (!gMouse.getState()) {
						mOField->DmgCard(card, 10);
						//mOField->update(); //check if "enemy-card" is dead
					}
				} // else
			}// if card is active
			//-----
			if (!gMouse.getState()) //
			{
				misUsingACard = false;
			}
		}
	}//for-loop
	*/


	// NEW

	if (battlecry_active)
	{
		if (ba_card != -1)
		{
			if (mCard[ba_card]->activateEffect())
			{
				

				battlecry_active = false;
				gMouse.BtnUp();
				ba_card = -1;
				return true;
			}
		}
		else
		{
			if (Effect_Field.checkEffect())
			{
				

				battlecry_active = false;
				gMouse.BtnUp();
				ba_card = -1;
				Effect_Field.reset();
				return true;
				
			}
		}
		TargetCard.move(gMouse.getX_df(), gMouse.getY_df());
		return false;
	}
	else
	{
		int PLaboveCard = getMouseAboveCard();
		if (PLaboveCard != -1)
		{
			mHoverEffectTexture.setPos(mPosX[mCardPosIndex[PLaboveCard]] - 5, mPosY[mCardPosIndex[PLaboveCard]] -5);
			mHoverEffectTexture.set(true);
		}
		else
			if (!mArrowAttackCard.isActive())
			mHoverEffectTexture.set(false);

		if (gMouse.isPressed() && !mArrowAttackCard.isActive() && PLaboveCard > -1)
		{
			mArrowAttackCard.setPos(getCardAt(PLaboveCard)->getPosX() + 32,
				getCardAt(PLaboveCard)->getPosY() + getCardAt(PLaboveCard)->getHeight() / 4);
			mArrowAttackCard.setActive(); //activate attack arrow
			mActiveCard = PLaboveCard;

			mHoverEffectTexture.setPos(mPosX[mCardPosIndex[PLaboveCard]] - 5, mPosY[mCardPosIndex[PLaboveCard]] - 5);
			mHoverEffectTexture.set(true);
		}
		else if (mArrowAttackCard.isActive())
		{

			int OPaboveCard = mOppField.lock()->getMouseAboveCard();

			if (OPaboveCard > -1)
			{
				mArrowAttackTarget.setPos(mOppField.lock()->getCardAt(OPaboveCard)->getPosX() + 32,
					mOppField.lock()->getCardAt(OPaboveCard)->getPosY() + mOppField.lock()->getCardAt(OPaboveCard)->getHeight() / 4);
				mArrowAttackTarget.setActive();



				if (!gMouse.isPressed()) {
					mOppField.lock()->DmgCard(OPaboveCard, std::dynamic_pointer_cast<MonsterCard>(getCardAt(mActiveCard))->getAttack());
					DmgCard(mActiveCard, dynamic_pointer_cast<MonsterCard>(mOppField.lock()->getCardAt(OPaboveCard))->getAttack());
					//mOField->update(); //check if "enemy-card" is dead
					mFieldNumberPopups.add(dynamic_pointer_cast<MonsterCard>(mOppField.lock()->getCardAt(OPaboveCard))->getAttack(), mCard[mActiveCard]->getPosX(),mCard[mActiveCard]->getPosY()); // NUMBER POPUP
				}
			}

			else if (mOppHero.lock()->mouseIsAbove())
			{
				mArrowAttackTarget.setPos(mOppHero.lock()->getX(), mOppHero.lock()->getY());
				mArrowAttackTarget.setActive();

				if (!gMouse.isPressed()) {
					mOppHero.lock()->dealDmg(dynamic_pointer_cast<MonsterCard>(mCard[mActiveCard])->getAttack());
					mFieldNumberPopups.add(dynamic_pointer_cast<MonsterCard>(mCard[mActiveCard])->getAttack(), mOppHero.lock()->getX()-5, mOppHero.lock()->getY()-28); // NUMBER POPUP
				}

			}

			else { mArrowAttackTarget.setInactive(); }


		}




		if (!gMouse.isPressed())
		{
			mArrowAttackCard.setInactive();
			mArrowAttackTarget.setInactive();
		}


		//reset and delete dead cards
		for (int i = 0; i < 7; i++)
		{
			if (mCard[i] != nullptr) {
				if (!dynamic_pointer_cast<MonsterCard>(mCard[i])->isAlive())
				{

					removeCard(i);
					//updatePosition();
				}
			}

		}
	}
	return true;
	
}
void Player_Field::render()
{
	
	bool hoverIsActive = false;

	
	drawRect(mData);

	mBackground.render();

	mHoverEffectTexture.render();

	Effect_Field.render();

	for (int i = 0; i < 7; i++)
	{
		if (mCard[i] != nullptr) {
			if (mFieldHasACard[i])
			{
				mCard[i]->render();
			
			}
		
		}
	}
	if (mArrowAttackCard.isActive()) { mArrowAttackCard.render(); }
	if (mArrowAttackTarget.isActive()) { mArrowAttackTarget.render(); }

	if (battlecry_active)
	{
		TargetCard.render();
	}

	if (hover != -1)
	{
		mCard[hover]->renderHoverEffect();
	}
	mFieldNumberPopups.render();
}

bool Player_Field::isInside(int x, int y)
{
	if (x > mData.x && x < mData.x + mData.w &&
		y > mData.y && y < mData.y + mData.h)
	{
		return true;
	}
	else { return false; }
}

void Player_Field::setField(const std::weak_ptr<Opponent_Field>& OppField)
{
	mOppField = OppField;
}
void Player_Field::setHero(const std::weak_ptr<Hero>& hero)
{
	mOppHero = hero;
}