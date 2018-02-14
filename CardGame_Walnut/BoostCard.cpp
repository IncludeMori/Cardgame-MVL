#include "BoostCard.hpp"

#include "Default_Card.hpp"

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

bool BoostCard::activate(Basic_Card *card)
{
	



	if (mTarget != eTarget::SELF)
		return activate();
	else //->Boost self (card => *this)
	{
		switch (mStat)
		{
		case(eStat::ATTACK):
			dynamic_cast<Default_Card*>(card)->increaseAtk(mAmount);
			break;
		case(eStat::HEALTH):
			dynamic_cast<Default_Card*>(card)->increaseHealth(mAmount);
			break;
		case(eStat::COST):
			dynamic_cast<Default_Card*>(card)->increaseCost(mAmount);
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
				if (mDeck->CardAt(i) != nullptr)
					dynamic_pointer_cast<Default_Card>(mDeck->CardAt(i))->increase(mStat, mAmount);
				i--;
			}
			
			break; // ALL
		case(eTarget_spec::RANDOM):  //->Boost one random card
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mDeck->getSize();
			if (mDeck->CardAt(rnd) != nullptr)
			{
				dynamic_pointer_cast<Default_Card>(mDeck->CardAt(rnd))->increase(mStat, mAmount);
			}
			else
			{
				std::cout << "Error: Boost Deck(Random)" << std::endl;
				std::cout << "Checked card:" << rnd << " || Deck Size: " << mDeck->getSize() << std::endl;
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
			for (int i = 0; i < mHand->getSize(); i++)
			{
				dynamic_pointer_cast<Default_Card>(mHand->CardAt(i))->increase(mStat, mAmount);
			}
			break;//ALL
		case(eTarget_spec::RANDOM):
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mHand->getSize();
			if (mHand->CardAt(rnd) != nullptr)
				dynamic_pointer_cast<Default_Card>(mHand->CardAt(rnd))->increase(mStat, mAmount);
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
			for (int i = 0; i < mField->getSize(); i++)
				dynamic_pointer_cast<Default_Card>(mField->CardAt(i))->increase(mStat, mAmount);
			for (int i = 0; i < mOpponentField->getSize(); i++)
				dynamic_pointer_cast<Default_Card>(mOpponentField->CardAt(i))->increase(mStat, mAmount);
			break;
		case(eTarget_spec::RANDOM):
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mHand->getSize();
			dynamic_pointer_cast<Default_Card>(mField->CardAt(rnd))->increase(mStat, mAmount);
			break;
		case(eTarget_spec::TARGET):

			if (mField->ChooseCard() == true) // used by AI
				return true;
			else
			{
				for (int i = 0; i < mField->getSize(); i++)
				{
					if (dynamic_pointer_cast<Default_Card>(mField->CardAt(i))->MouseIsAbove() && gMouse.isPressed())
					{
						dynamic_pointer_cast<Default_Card>(mField->CardAt(i))->increase(mStat, mAmount);
						return true;
					}

				}
				for (int i = 0; i < mOpponentField->getSize(); i++)
				{
					if (dynamic_pointer_cast<Default_Card>(mOpponentField->CardAt(i))->MouseIsAbove() && gMouse.isPressed())
					{
						dynamic_pointer_cast<Default_Card>(mOpponentField->CardAt(i))->increase(mStat, mAmount);
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
