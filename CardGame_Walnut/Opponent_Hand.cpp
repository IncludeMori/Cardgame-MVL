#include "Opponent_Hand.hpp"

#include <memory>

using std::dynamic_pointer_cast;

Opponent_Hand::Opponent_Hand()
{
	mSize = 0;
	int height = 243;
	int width = 165;
	//cards pos
	int test = 1;
	int x = SCREEN_WIDTH / 2 - width / 2, y = -height / 2 -20;
	int change = 200;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		mPlayable[i] = false;
		mCard_isActive[i] = false;

		mPosY[i] = y;
		mPosX[i] = x;

		x = x + test*change;
		change = change *-1;
		test++;
	}

	mResource.setPos(SCREEN_WIDTH / 2 + 2 * mResource.getWidth()+10, mResource.getHeight() * 4.5 -5,1);
}

std::shared_ptr<Basic_Card> Opponent_Hand::getBestCard()
{
	int index = -1;
	int highest = -1;

	for (int i = 0; i < mSize; i++)
	{
		if (mCard[i] != nullptr) {
			if (dynamic_pointer_cast<Default_Card>(mCard[i])->getAttack() > highest && mCard[i]->getCost() <= mResource.getAvailable())
			{
				highest = dynamic_pointer_cast<Default_Card>(mCard[i])->getAttack();
				index = i;
		
			}
		}
	}
	
	if (index > -1) {
		
		mResource.removeAv(mCard[index]->getCost());
		return getCard(index);
	}
	else
	return nullptr;

}

bool Opponent_Hand::canPlayCard()
{

	for (int i = 0; i < mSize; i++)
	{
		if (mCard[i] == nullptr)
			__debugbreak();
		if (mCard[i]->getCost() <= mResource.getAvailable())
		{
			return true;
		}
	}

	//otherwise
	return false;


}
void Opponent_Hand::render()
{
	mResource.render();
		for (int i = 0; i < mSize; i++)
		{
			if (mCard[i] != nullptr) { mCard[i]->renderBackside(); }
		}
}