#include "Opponent_Field.hpp"

#include <iostream>

#include <memory>

using std::dynamic_pointer_cast;

Opponent_Field::Opponent_Field()
{
	mSize = 0;
	//Field data
	mData = { 50,SCREEN_HEIGHT/4,SCREEN_WIDTH-2*50,SCREEN_HEIGHT/4 };


	//Init Card X&Y pos
	int x = SCREEN_WIDTH / 2 - 165 / 2;
	int y = SCREEN_HEIGHT / 4+15;
	int change = 185;
	int lol = change;
	for (int i = 0; i <= mMax_Size; i++)
	{
		mPosY[i] = y;
		mPosX[i] = x;
		std::cout << "X:" << x << std::endl;
		std::cout << "Y:" << y << std::endl;
		x += change;
		if (change > 0) { change = (change + lol) *-1; }
		else { change = (change + (lol*-1))*-1; }
	}
	mPosY[0] = mPosY[1];

}
Opponent_Field::~Opponent_Field()
{
	
}

void Opponent_Field::update()
{
	for (int i = 0; i < 7; i++)
	{
		if (mCard[i] != nullptr) {
			if (!dynamic_pointer_cast<Default_Card>(mCard[i])->isAlive())
			{
				mCard[i].reset();
				mCard[i] = nullptr;
				//updatePosition();
			}
		}
		
	}
}

bool Opponent_Field::ChooseCard()
{
	return true;
}

void Opponent_Field::attack()
{
	int cardIndex = -1;
	int targetIndex = -1;

	int i = 0;
	while (cardIndex == -1)
	{
		if (dynamic_pointer_cast<Default_Card>(mCard[i])->canAttack())
		{
			mAttackCard.setPos(mCard[i]->getX(), mCard[i]->getY());
			mAttackCard.setActive();
			cardIndex = i;

		}
		i++;
	}

	while (targetIndex == -1)
	{
		if (mPlayerField->CardAt(i) != nullptr)
		{
			mPlayerField->DmgCard(i, dynamic_pointer_cast<Default_Card>(mCard[cardIndex])->getAttack());
			targetIndex = 1;
		}
	}

}

void Opponent_Field::setHero(const std::shared_ptr<Hero>& hero)
{
	mPlayerHero = hero;
}

void Opponent_Field::setField(const std::shared_ptr<Field>& field)
{
	mPlayerField = field;
}

