#include "HealOrDmg.hpp"

#include "BaseCard.hpp"
#include "MonsterCard.hpp"

#include "Field.hpp"
#include <memory>

#include "gMouse.hpp"

#include <iostream>

HealOrDmg::HealOrDmg()
{
}

HealOrDmg::HealOrDmg(int amount)
{
	mAmount = amount;
}


HealOrDmg::~HealOrDmg()
{
}



bool HealOrDmg::activate(BaseCard * card)
{
	return false;
}

bool HealOrDmg::activate()
{
	if (mField.lock()->ChooseCard() == true) // used by AI
		return true;
	else
	{
		if (mAmount < 1)
		{
			for (int i = 0; i < mField.lock()->getSize(); i++)
			{
				if (std::dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(i))->mouseIsAbove() && gMouse.isPressed())
				{
					mOpponentField.lock()->DmgCard(i, mAmount);
					std::cout << "TARGET:" << i << std::endl;
					return true;
				}

			}
			if (mOpponentField.lock() != nullptr)
			{
				for (int i = 0; i < mOpponentField.lock()->getSize(); i++)
				{
					if (std::dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->CardAt(i))->mouseIsAbove() && gMouse.isPressed())
					{
						mOpponentField.lock()->DmgCard(i, mAmount);
						std::cout << "TARGET:" << i << std::endl;
						return true;
					}

				}
			}
			else
				std::cout << "NULLPTR";
		}
		else
		{
			for (int i = 0; i < mField.lock()->getSize(); i++)
			{
				if (std::dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(i))->mouseIsAbove() && gMouse.isPressed())
				{
					std::dynamic_pointer_cast<MonsterCard>(mField.lock()->CardAt(i))->increase(eStat::HEALTH, mAmount);
					std::cout << "TARGET:" << i << std::endl;
					return true;
				}

			}
			if (mOpponentField.lock() != nullptr)
			{
				for (int i = 0; i < mOpponentField.lock()->getSize(); i++)
				{
					if (std::dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->CardAt(i))->mouseIsAbove() && gMouse.isPressed())
					{
						std::dynamic_pointer_cast<MonsterCard>(mOpponentField.lock()->CardAt(i))->increase(eStat::HEALTH, mAmount);
						std::cout << "TARGET:" << i << std::endl;
						return true;
					}

				}
			}
			else
				std::cout << "NULLPTR";
		}
		return false;
	}
}
