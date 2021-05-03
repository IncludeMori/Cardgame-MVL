#include "BoostCard.hpp"

#include "MonsterCard.hpp"

#include "Player_Hand.hpp"

#include "Deck.hpp"
#include "Field.hpp"
#include "Hand.hpp"

#include <stdlib.h>     
#include <time.h>       
#include "gMouse.hpp"

#include <memory>

using std::dynamic_pointer_cast;

BoostCard::BoostCard()
{

}
BoostCard::BoostCard(eTarget target, eTarget_spec target_spec, eStat stat, int amount)
{
	mTarget = target;
	mTarget_spec = target_spec;
	mStat = stat;
	mAmount = amount;
}
BoostCard::~BoostCard()
{
}

bool BoostCard::activate(BaseCard *card)
{
	



	if (mTarget != eTarget::SELF)
		return activate();
	else //->Boost self (card => *this)
	{
		switch (mStat)
		{
		case(eStat::ATTACK):
			dynamic_cast<MonsterCard*>(card)->increaseAtk(mAmount);
			break;
		case(eStat::HEALTH):
			dynamic_cast<MonsterCard*>(card)->increaseHealth(mAmount);
			break;
		case(eStat::COST):
			dynamic_cast<MonsterCard*>(card)->modifyCost(mAmount);
			break;
		case(eStat::ERROR):
			return false;
			break;
		}
		return true;
	}
}

bool BoostCard::activate()
{
	std::cout << "Effect:" << (int)mTarget << std::endl;
	std::cout << "Target:" << (int)mTarget_spec << std::endl;

	switch (mTarget)
	{
	case(eTarget::DECK):
    //--------------------------------------------------
		switch (mTarget_spec)
		{
		case(eTarget_spec::ALL):
			int i;
			i = 29;
			while (i >= 0)
			{
				if (mDeck.lock()->CardAt(i) != nullptr)
					dynamic_pointer_cast<MonsterCard>(mDeck.lock()->CardAt(i))->increase(mStat, mAmount);
				i--;
			}
			
			break; // ALL
		case(eTarget_spec::RANDOM):  //->Boost one random card
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mDeck.lock()->getSize();
			if (mDeck.lock()->CardAt(rnd) != nullptr)
			{
				dynamic_pointer_cast<MonsterCard>(mDeck.lock()->CardAt(rnd))->increase(mStat, mAmount);
			}
			else
			{
				std::cout << "Error: Boost Deck(Random)" << std::endl;
				std::cout << "Checked card:" << rnd << " || Deck Size: " << mDeck.lock()->getSize() << std::endl;
			}
			break; // RANDOM
		default:
			return false;
		}

		break;//DECK
	case(eTarget::HAND):
	//--------------------------------------------------
		switch (mTarget_spec)
		{
		case(eTarget_spec::ALL):
			for (int i = 0; i < mHand.lock()->getSize(); i++)
			{
				dynamic_pointer_cast<MonsterCard>(mHand.lock()->CardAt(i))->increase(mStat, mAmount);
			}
			break;//ALL
		case(eTarget_spec::RANDOM):
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mHand.lock()->getSize();
			if (mHand.lock()->CardAt(rnd) != nullptr)
				dynamic_pointer_cast<MonsterCard>(mHand.lock()->CardAt(rnd))->increase(mStat, mAmount);
			else
				std::cout << "Error: Boost Hand(Random)" << std::endl;
			break;//RANDOM
		default:
			return false;
		}
		break;//HAND
	case(eTarget::FIELD):
	//--------------------------------------------------	
		switch (mTarget_spec)
		{
		case(eTarget_spec::ALL):
			for (int i = 0; i < mField.lock()->getSize(); i++)
				dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(i))->increase(mStat, mAmount);
			for (int i = 0; i < mOpponentField.lock()->getSize(); i++)
				dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->CardAt(i))->increase(mStat, mAmount);
			break;
		case(eTarget_spec::RANDOM):
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mHand.lock()->getSize();
			dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(rnd))->increase(mStat, mAmount);
			break;
		case(eTarget_spec::TARGET):

			if (mField.lock()->ChooseCard() == true) // used by AI
				return true;
			else
			{
				for (int i = 0; i < mField.lock()->getSize(); i++)
				{
					if (dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(i)) != nullptr)
					if (dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(i))->mouseIsAbove() && gMouse.isPressed())
					{
						dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(i))->increase(mStat, mAmount);
						return true;
					}

				}
				for (int i = 0; i < mOpponentField.lock()->getSize(); i++)
				{
					if (dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->CardAt(i)) != nullptr)
					if (dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->CardAt(i))->mouseIsAbove() && gMouse.isPressed())
					{
						dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->CardAt(i))->increase(mStat, mAmount);
						return true;
					}

				}
				return false;
			}

			break;
		default:
			return false;
		}
		break;//FIELD
	//--------------------------------------------------
	default:
		return true;
	}
	return true;
}
