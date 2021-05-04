#include "BaseCard.hpp"

#include "Deck.hpp"
#include "Field.hpp"
#include "Hand.hpp"

#include "gMouse.hpp"

#include "Place.hpp"

#include "Card_Stats_Type.hpp"

void BaseCard::renderHoverEffect()
{
	mHoverEffectTexture.render();
}

bool BaseCard::setStuff(const std::weak_ptr<Deck> &deck, const std::weak_ptr<Hand> &hand, const std::weak_ptr<Field> &field, const std::weak_ptr<Field> &oppfield)
{
	if (oppfield.lock() == nullptr)
		__debugbreak();
	return mEffect->setStuff(deck, hand, field,oppfield);
}

void BaseCard::changePlacePosition(Position newpos)
{
	mPlacePosition = newpos;
}

void BaseCard::update()
{
	mHoverEffectTexture.update();
}

void BaseCard::move(int x, int y)
{
	mPosX += x;
	mPosY += y;

	for (auto &i : mStatsIcon)
		i.move(x, y);

	mFrame.setPos(mPosX, mPosY);
	mIcon.setPos(mPosX, mPosY);
	moveIcons(x, y);
	mBackground.setPos(mPosX, mPosY);
}

void BaseCard::setActive()
{
	mActive = true;
}
void BaseCard::setInactive()
{
	mActive = false;
}
bool BaseCard::isActive()
{
	return mActive;
}

bool BaseCard::mouseIsAbove()
{
	return false;
}

void BaseCard::modifyCost(int amount)
{
	mBasicPlayCost += amount;
}

int BaseCard::getCost()
{
	return mBasicPlayCost;
}





