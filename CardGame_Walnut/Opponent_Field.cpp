#include "Opponent_Field.hpp"

#include <iostream>

#include <memory>
#include <boost/range/irange.hpp>

using std::dynamic_pointer_cast;

using namespace boost;

Opponent_Field::Opponent_Field()
{
	mSize = 0;
	//Field data
	mData = { 50,SCREEN_HEIGHT/4,SCREEN_WIDTH-2*50,SCREEN_HEIGHT/4 };

	// Init Card X&Y pos     
	int x = SCREEN_WIDTH / 2 - 165 / 2;
	int y = SCREEN_HEIGHT / 4 + 15;
	int change = 185;
	x = x - 3 * change;

	for (int i : irange(0, MAX_SIZE))
	{
		mPosX[i] = x;
		mPosY[i] = y;
		x += change;
		mCard[i] = nullptr;
	}
}
Opponent_Field::~Opponent_Field()
{
	
}

void Opponent_Field::update()
{
	for (int i = 0; i < 7; i++)
	{
		if (mCard[i] != nullptr) {
			if (!dynamic_pointer_cast<MonsterCard>(mCard[i])->isAlive())
			{
				removeCard(i);
			}
		}
		
	}

	int PLaboveCard = getMouseAboveCard();
	if (PLaboveCard != -1)
	{
		mHoverEffectTexture.setPos(mPosX[mCardPosIndex[PLaboveCard]] - 5, mPosY[mCardPosIndex[PLaboveCard]] - 5);
		mHoverEffectTexture.set(true);
	}
	else
		if (!mArrowAttackCard.isActive())
			mHoverEffectTexture.set(false);
}


void Opponent_Field::addCard(const std::shared_ptr<BaseCard>& card, int index)
{
	if (index != -1 && mSize >= 1 && card != nullptr)
		if (mCard[getFieldIndexFromCardAt(index)] == nullptr)
		{
			//außerhalb der gespielten Karten
			if (index > 3)
			{
				//rightmost card
				int rechtesteKarte = -1;
				for (int i : irange(0, MAX_SIZE))
					if (mCardPosIndex[i] >= 4)
						if (mCard[i] != nullptr)
							if (mCardPosIndex[i] > rechtesteKarte)
								rechtesteKarte = mCardPosIndex[i];


				index = rechtesteKarte + 1;
				if (rechtesteKarte == -1)
					index = 4;

				mLastCardPlacedAt = CardPlace::RIGHT;
			}
			else
			{
				//leftmost card
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

				index = linksteKarte - 1;
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


		if (card == nullptr) {}
		else
		{
			mSize++;
			mCard[mSize - 1] = card;
			mFieldHasACard[mSize - 1] = true;
			std::dynamic_pointer_cast<MonsterCard>(mCard[mSize - 1])->changePlacePosition(Position::FIELD);
			mCard[mSize - 1]->setPos(mPosX[mSize - 1], mPosY[mSize - 1]);
			if (std::dynamic_pointer_cast<MonsterCard>(mCard[mSize - 1])->getEffect() == eEffect::BATTLECRY)
				mCard[mSize - 1]->activateEffect();

		}
		if (mSize>1)
			organizeField();
	}

	updatePositions();



}


bool Opponent_Field::ChooseCard()
{
	return true;
}

void Opponent_Field::attack()
{
	int cardIndex = -1;
	int targetIndex = -1;

	int currentIndex = 0;
	while (cardIndex == -1)
	{
		if (dynamic_pointer_cast<MonsterCard>(mCard[currentIndex])->canAttack())
		{
			mArrowAttackCard.setPos(mCard[currentIndex]->getPosX(), mCard[currentIndex]->getPosY());
			mArrowAttackCard.setActive();
			cardIndex = currentIndex;

		}
		currentIndex++;
	}

	while (targetIndex == -1)
	{
		if (mPlayerField.lock()->getCardAt(currentIndex) != nullptr)
		{
			mPlayerField.lock()->DmgCard(currentIndex, dynamic_pointer_cast<MonsterCard>(mCard[cardIndex])->getAttack());
			targetIndex = 1;
		}
	}

}

void Opponent_Field::setHero(const std::weak_ptr<Hero>& hero)
{
	mPlayerHero = hero;
}

void Opponent_Field::setField(const std::weak_ptr<Field>& field)
{
	mPlayerField = field;
}

