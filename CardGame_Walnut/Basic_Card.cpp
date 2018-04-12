#include "Basic_Card.hpp"

#include "Deck.hpp"
#include "Field.hpp"
#include "Hand.hpp"

#include "gMouse.hpp"

#include "Place.hpp"

void Basic_Card::renderHoverEffect()
{
	HoverEffect.render();
}

bool Basic_Card::setStuff(const std::shared_ptr<Deck> &deck, const std::shared_ptr<Hand> &hand, const std::shared_ptr<Field> &field, const std::shared_ptr<Field> &oppfield)
{
	if (oppfield == nullptr)
		__debugbreak();
	return mEffect->setStuff(deck, hand, field,oppfield);
}

void Basic_Card::changePosition(Position newpos)
{
	mPos = newpos;
}

void Basic_Card::move(int x, int y)
{
	mPosX += x;
	mPosY += y;

	mFrame.setPos(mPosX, mPosY);
	mIcons.setPos(mPosX, mPosY);
	moveSigns(x, y);


	mBackground.setPos(mPosX, mPosY);

}

void Basic_Card::setActive()
{
	mActive = true;
}
void Basic_Card::setInactive()
{
	mActive = false;
}
bool Basic_Card::isActive()
{
	return mActive;
}

bool Basic_Card::MouseIsAbove()
{
	return false;
	if (gMouse.isPressed())
	{
		if (HoverEffect.isActive())
		{
			HoverEffect.disable();
		}
	}
	else
		if (mPos == Position::HAND)
			HoverEffect.enable();


	int mouseX = gMouse.getX();
	int mouseY = gMouse.getY();
	if (mouseX > mPosX && mouseX < mPosX + mWidth && mouseY > mPosY && mouseY < mPosY + mHeight)
	{
		return true;
	}
	else
		return false;
}

void Basic_Card::increaseCost(int amount)
{
	mBasicCost += amount;
}

int Basic_Card::getCost()
{
	return mBasicCost;
}





