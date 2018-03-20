#include "Player_Field.hpp"

#include "gScreenSize.hpp"
#include "gRenderer.hpp"
#include "gMouse.hpp"
#include <iostream>
#include <boost/range/irange.hpp>

#include <memory>

using std::dynamic_pointer_cast;

using namespace boost;

Player_Field::Player_Field()
{

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

void Player_Field::addCard(const std::shared_ptr<Basic_Card>& card)
{

	int posX = card->getX();
	int posY = card->getY();
	int index = -1;
	
	//find pos
	
	//search for index -> player wants to add card@index
	for (int i : irange(0,MAX_SIZE))
	{
		if (posX > mPosX[i] && posX < mPosX[i] + 200)
			index = i;
	}
	std::cout << "INDEX:" << index << std::endl;
	if (index != -1 && mSize >= 1 && card != nullptr)
		if (mCard[getCardAt(index)] == nullptr)
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

				last_added = Last_Added::RIGHT;
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
							std::cout << "i:" << i << std::endl;
							std::cout << "cardindex:" << mCardPosIndex[i] << std::endl;
							if (mCardPosIndex[i] < linksteKarte)
							{
								linksteKarte = mCardPosIndex[i];
								std::cout << "linkste karte new:" << linksteKarte;
							}
						}

				index = linksteKarte-1;
				if (linksteKarte == 3)
					index = 2;

				std::cout << "linkeste Karte:" << index << std::endl;
				last_added = Last_Added::LEFT;

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
		mCard[mSize - 1]->changePosition(Position::FIELD);
		mCard_isActive[mSize - 1] = true;
		mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
		if (dynamic_pointer_cast<Default_Card>(mCard[mSize - 1])->getEffect() == eEffect::BATTLECRY)
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
void Player_Field::addEffectCard(const std::shared_ptr<Basic_Card>& card)
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
	/*
	int card = 0; //...

	for (int i = 0; i < mSize; i++)
	{
		if (mCard[i] != nullptr) {
			//check if player wants to use card
			if (gMouse.getState() && mCard[i]->MouseIsAbove() && !misUsingACard)
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
					if (mOField->CardAt(card) != nullptr)
					{
						mAttackArrow.setPos(mOField->CardAt(card)->getX() + mOField->CardAt(card)->getWidth() / 4,
							mOField->CardAt(card)->getY() + mOField->CardAt(card)->getHeight() / 4);
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

		if (gMouse.isPressed() && !mAttackCard.isActive() && PLaboveCard > -1)
		{
			mAttackCard.setPos(CardAt(PLaboveCard)->getX() + 32,
				CardAt(PLaboveCard)->getY() + CardAt(PLaboveCard)->getHeight() / 4);
			mAttackCard.setActive(); //activate attack arrow
			mActiveCard = PLaboveCard;
		}
		else if (mAttackCard.isActive())
		{

			int OPaboveCard = mOppField->getMouseAboveCard();

			if (OPaboveCard > -1)
			{
				mAttackTarget.setPos(mOppField->CardAt(OPaboveCard)->getX() + 32,
					mOppField->CardAt(OPaboveCard)->getY() + mOppField->CardAt(OPaboveCard)->getHeight() / 4);
				mAttackTarget.setActive();



				if (!gMouse.isPressed()) {
					mOppField->DmgCard(OPaboveCard, std::dynamic_pointer_cast<Default_Card>(CardAt(mActiveCard))->getAttack());
					DmgCard(mActiveCard, dynamic_pointer_cast<Default_Card>(mOppField->CardAt(OPaboveCard))->getAttack());
					//mOField->update(); //check if "enemy-card" is dead
					mFieldNumberPopups.add(dynamic_pointer_cast<Default_Card>(mOppField->CardAt(OPaboveCard))->getAttack(), mCard[mActiveCard]->getX(),mCard[mActiveCard]->getY()); // NUMBER POPUP
				}
			}

			else if (mOppHero->MouseIsAbove())
			{
				mAttackTarget.setPos(mOppHero->getX(), mOppHero->getY());
				mAttackTarget.setActive();

				if (!gMouse.isPressed()) {
					mOppHero->dealDmg(dynamic_pointer_cast<Default_Card>(mCard[mActiveCard])->getAttack());
					mFieldNumberPopups.add(dynamic_pointer_cast<Default_Card>(mCard[mActiveCard])->getAttack(),mOppHero->getX()-5,mOppHero->getY()-28); // NUMBER POPUP
				}

			}

			else { mAttackTarget.setInactive(); }


		}




		if (!gMouse.isPressed())
		{
			mAttackCard.setInactive();
			mAttackTarget.setInactive();
		}


		//reset and delete dead cards
		for (int i = 0; i < 7; i++)
		{
			if (mCard[i] != nullptr) {
				if (!dynamic_pointer_cast<Default_Card>(mCard[i])->isAlive())
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
	int hover = -1;
	bool hoverIsActive = false;

	
	drawRect(mData);

	mBackground.render();

	Effect_Field.render();

	for (int i = 0; i < 7; i++)
	{
		if (mCard[i] != nullptr) {
			if (mCard_isActive[i])
			{
				mCard[i]->render(hoverIsActive);
				if (hoverIsActive)
				{
					hover = i;
					hoverIsActive = false;
				}
			}
		
		}
	}
	if (mAttackCard.isActive()) { mAttackCard.render(); }
	if (mAttackTarget.isActive()) { mAttackTarget.render(); }

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

void Player_Field::setField(const std::shared_ptr<Opponent_Field>& OppField)
{
	mOppField = OppField;
}
void Player_Field::setHero(const std::shared_ptr<Hero>& hero)
{
	mOppHero = hero;
}



void Player_Field::removeCard(int index)
{
	mCard[index].reset();
	mCard[index] = nullptr;
	mSize--;

	for (int i : irange(0, MAX_SIZE))
	{
		if (mCardPosIndex[i] > index)
			mCardPosIndex[i]--;
	}
	mCardPosIndex[index] = MAX_SIZE-1;

	updatePositions();


	//update field position

}

void Player_Field::updateFieldWithNewCard(int index)
{
	//index = 1
	// 1 should go to 2
	// 0 should stay at 0
	//all move to 1???
	for (int i : irange(0, mSize))
		if (mCardPosIndex[i] >= index)
			mCardPosIndex[i]++;
	mCardPosIndex[mSize] = index;

	updatePositions();
}

void Player_Field::updatePositions()
{
	for (int i : irange(0, mSize))
	{
		mCard[i]->setPos(mPosX[mCardPosIndex[i]], mPosY[mCardPosIndex[i]]);

		std::cout << "Card@" << i << " set to index" << mCardPosIndex[i] << std::endl;

	}
}

void Player_Field::organizeField()
{
	if (last_added == Last_Added::LEFT)
	{
		if (mSize%2 == 0)
		for (int i : irange(0, MAX_SIZE))
			mCardPosIndex[i]++;
	}
	else
	{
		if (mSize%2 == 1)
		for (int i : irange(0, MAX_SIZE))
			mCardPosIndex[i]--;
	}
}

int Player_Field::getCardAt(int index)
{
	
	for (int i = 0;i<MAX_SIZE;i++)
	{
		if (mCardPosIndex[i] == index)
			return i;
	}
	return 6;
}