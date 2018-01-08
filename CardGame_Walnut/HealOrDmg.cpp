#include "HealOrDmg.hpp"

#include "Basic_Card.hpp"
#include "Default_Card.hpp"

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



bool HealOrDmg::activate(Basic_Card * card)
{
	return false;
}

bool HealOrDmg::activate()
{
	if (mField->ChooseCard() == true) // used by AI
		return true;
	else
	{
		if (mAmount < 1)
		{
			for (int i = 0; i < mField->getSize(); i++)
			{
				if (std::dynamic_pointer_cast<Default_Card>(mField->CardAt(i))->MouseIsAbove() && gMouse.isPressed())
				{
					mOpponentField->DmgCard(i, mAmount);
					std::cout << "TARGET:" << i << std::endl;
					return true;
				}

			}
			if (mOpponentField != nullptr)
			{
				for (int i = 0; i < mOpponentField->getSize(); i++)
				{
					if (std::dynamic_pointer_cast<Default_Card>(mOpponentField->CardAt(i))->MouseIsAbove() && gMouse.isPressed())
					{
						mOpponentField->DmgCard(i, mAmount);
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
			for (int i = 0; i < mField->getSize(); i++)
			{
				if (std::dynamic_pointer_cast<Default_Card>(mField->CardAt(i))->MouseIsAbove() && gMouse.isPressed())
				{
					std::dynamic_pointer_cast<Default_Card>(mField->CardAt(i))->increase(eStat::HEALTH, mAmount);
					std::cout << "TARGET:" << i << std::endl;
					return true;
				}

			}
			if (mOpponentField != nullptr)
			{
				for (int i = 0; i < mOpponentField->getSize(); i++)
				{
					if (std::dynamic_pointer_cast<Default_Card>(mOpponentField->CardAt(i))->MouseIsAbove() && gMouse.isPressed())
					{
						std::dynamic_pointer_cast<Default_Card>(mOpponentField->CardAt(i))->increase(eStat::HEALTH, mAmount);
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
