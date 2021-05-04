#include "Player_Hand.hpp"

#include "gMouse.hpp"
#include <memory>

using std::dynamic_pointer_cast;

Player_Hand::Player_Hand()
{
	for (int i = 0; i < MAX_SIZE; i++)
		mShift[i] = 5;


	mSize = 0;
	int height = 243;
	int width = 165;
	//cards pos
	int test = 1;
	int x = SCREEN_WIDTH/2-width/2, y = SCREEN_HEIGHT-(height/2)+20;
	int change = 115;

	//!
	x = x - 4 * 125;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		mPlayable[i] = false;
		mCard_isActive[i] = false;

		mPosY[i] = y;
		mPosX[i] = x;
		
		x = x + change;
		//change = change *-1;
		test++;
	}

	mResource.setPos(SCREEN_WIDTH / 2 + 2*mResource.getWidth()+10, SCREEN_HEIGHT - mResource.getHeight() * 4.5 - 80,0);

}
Player_Hand::~Player_Hand()
{
	
}

void Player_Hand::startTurn()
{
	mResource.increase();
}


void Player_Hand::update(const std::shared_ptr<Player_Field> &mField)
{
	
	if (!gMouse.isPressed()) { isMovingACard = false; }
	
	for (int i = mSize-1; i >= 0; i--)
	{
		if (!mCard_isActive[i]) { mCard[i].reset(); } // remove pointer

		if (mCard[i] != nullptr)
		{
			if (mCard[i]->getCost() <= mResource.getAvailable())
			{
				mPlayable[i] = true;

				if (!isMovingACard) {
					//check if player wants to move the card
					if (gMouse.isPressed() &&
						mCard[i]->mouseIsAbove())
					{
						mCard[i]->setActive();
						std::cout << "Player is moving card:" << i << std::endl;
						isMovingACard = true;
					}
				}
				if (!gMouse.isPressed()) { mCard[i]->setInactive(); } //!error

				if (mCard[i]->isActive()) {
					mCard[i]->move(gMouse.getX_df(), gMouse.getY_df());
				}


				if (mField->isInside(getPosXFromCard(i), getPosYFromCard(i)) && !gMouse.isPressed() && isPlayable(i))
				{
					mResource.removeAv(mCard[i]->getCost());
					getCard(i)->play(mField);

					//mField->addCard(getCard(i));
					played(i);
				}
			}
		}

	}

	
}

void Player_Hand::played(int index)
{
	mPlayable[index] = false;
}
bool Player_Hand::isPlayable(int index)
{
	if (index < mSize)
		return mPlayable[index];
	else
		return false;
}