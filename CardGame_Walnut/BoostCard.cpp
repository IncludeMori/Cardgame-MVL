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
BoostCard::BoostCard(eTargetType target, eTargetTypeSpec target_spec, eTargetStatType stat, int amount)
{
	mTarget = target;
	mTargetSpec = target_spec;
	mStat = stat;
	mAmount = amount;
}
BoostCard::~BoostCard()
{
}

bool BoostCard::activate(BaseCard *card)
{
	



	if (mTarget != eTargetType::SELF)
		return activate();
	else //->Boost self (card => *this)
	{
		switch (mStat)
		{
		case(eTargetStatType::ATTACK):
			dynamic_cast<MonsterCard*>(card)->increaseAtk(mAmount);
			break;
		case(eTargetStatType::HEALTH):
			dynamic_cast<MonsterCard*>(card)->increaseHealth(mAmount);
			break;
		case(eTargetStatType::COST):
			dynamic_cast<MonsterCard*>(card)->modifyCost(mAmount);
			break;
		case(eTargetStatType::ERROR):
			return false;
			break;
		}
		return true;
	}
}

bool BoostCard::activate()
{
	std::cout << "Effect:" << (int)mTarget << std::endl;
	std::cout << "Target:" << (int)mTargetSpec << std::endl;

	switch (mTarget)
	{
	case(eTargetType::DECK):
    //--------------------------------------------------
		switch (mTargetSpec)
		{
		case(eTargetTypeSpec::ALL):
			int i;
			i = 29;
			while (i >= 0)
			{
				if (mDeck.lock()->getCardAt(i) != nullptr)
					dynamic_pointer_cast<MonsterCard>(mDeck.lock()->getCardAt(i))->increase(mStat, mAmount);
				i--;
			}
			
			break; // ALL
		case(eTargetTypeSpec::RANDOM):  //->Boost one random card
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mDeck.lock()->getSize();
			if (mDeck.lock()->getCardAt(rnd) != nullptr)
			{
				dynamic_pointer_cast<MonsterCard>(mDeck.lock()->getCardAt(rnd))->increase(mStat, mAmount);
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
	case(eTargetType::HAND):
	//--------------------------------------------------
		switch (mTargetSpec)
		{
		case(eTargetTypeSpec::ALL):
			for (int i = 0; i < mHand.lock()->getSize(); i++)
			{
				dynamic_pointer_cast<MonsterCard>(mHand.lock()->getCardAt(i))->increase(mStat, mAmount);
			}
			break;//ALL
		case(eTargetTypeSpec::RANDOM):
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mHand.lock()->getSize();
			if (mHand.lock()->getCardAt(rnd) != nullptr)
				dynamic_pointer_cast<MonsterCard>(mHand.lock()->getCardAt(rnd))->increase(mStat, mAmount);
			else
				std::cout << "Error: Boost Hand(Random)" << std::endl;
			break;//RANDOM
		default:
			return false;
		}
		break;//HAND
	case(eTargetType::FIELD):
	//--------------------------------------------------	
		switch (mTargetSpec)
		{
		case(eTargetTypeSpec::ALL):
			for (int i = 0; i < mField.lock()->getSize(); i++)
				dynamic_pointer_cast<MonsterCard>(mField.lock()->getCardAt(i))->increase(mStat, mAmount);
			for (int i = 0; i < mOpponentField.lock()->getSize(); i++)
				dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->getCardAt(i))->increase(mStat, mAmount);
			break;
		case(eTargetTypeSpec::RANDOM):
			srand((unsigned int)time(nullptr));
			int rnd;
			rnd = rand() % mHand.lock()->getSize();
			dynamic_pointer_cast<MonsterCard>(mField.lock()->getCardAt(rnd))->increase(mStat, mAmount);
			break;
		case(eTargetTypeSpec::TARGET):

			if (mField.lock()->ChooseCard() == true) // used by AI
				return true;
			else
			{
				for (int i = 0; i < mField.lock()->getSize(); i++)
				{
					if (dynamic_pointer_cast<MonsterCard>(mField.lock()->getCardAt(i)) != nullptr)
					if (dynamic_pointer_cast<MonsterCard>(mField.lock()->getCardAt(i))->mouseIsAbove() && gMouse.isPressed())
					{
						dynamic_pointer_cast<MonsterCard>(mField.lock()->getCardAt(i))->increase(mStat, mAmount);
						return true;
					}

				}
				for (int i = 0; i < mOpponentField.lock()->getSize(); i++)
				{
					if (dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->getCardAt(i)) != nullptr)
					if (dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->getCardAt(i))->mouseIsAbove() && gMouse.isPressed())
					{
						dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->getCardAt(i))->increase(mStat, mAmount);
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
