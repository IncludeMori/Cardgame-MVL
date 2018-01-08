#include "Hero.hpp"

#include "gScreenSize.hpp"
#include "gMouse.hpp"


Hero::Hero()
{
	mIsAlive = true;
	std::string path = "Data/hero.png";
	mPortrait.loadFromFile(path);

	mPosX = SCREEN_WIDTH / 2 - 75;
	mPosY = SCREEN_HEIGHT - 3 * (SCREEN_HEIGHT / 4) - 150;
	
	mHPSign.setPos(mPosX, mPosY);

	mPortrait.setPos(mPosX, mPosY);
}
Hero::Hero(int v,int amount)
{
	mIsAlive = true;
	std::string path = "Data/hero.png";
	

	if (v == 0)
	{
		mPosX = SCREEN_WIDTH / 2 - 75;
		mPosY = SCREEN_HEIGHT - SCREEN_HEIGHT / 4;
	}
	else {
		mPosX = SCREEN_WIDTH / 2 - 75;
		mPosY = SCREEN_HEIGHT - 3 * (SCREEN_HEIGHT / 4) - 150;
		path = "Data/hero_opp.png";
	}
	mPortrait.loadFromFile(path);

	mHPSign.setPos(mPosX, mPosY);
	mHPSign.changeData(amount);

	mPortrait.setPos(mPosX, mPosY);

}
Hero::~Hero()
{

}

void Hero::render()
{
	mPortrait.render();
	mHPSign.render();
}

void Hero::dealDmg(int amount)
{
	mHPSign.add(-amount);

	if (mHPSign.getCurrentData() <= 0) { mIsAlive = false; }
}
bool Hero::MouseIsAbove()
{
	if (gMouse.getX() > mPosX && gMouse.getX() < mPosX + mPortrait.getWidth() && gMouse.getY() > mPosY && gMouse.getY() < mPosY + mPortrait.getHeight())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Hero::setAlpha(Uint8 alpha)
{
	mPortrait.setAlpha(alpha);
}
bool Hero::isAlive()
{
	return mIsAlive;
}
int Hero::getX()
{
	return mPosX;
}
int Hero::getY()
{
	return mPosY;
}
int Hero::getHeight()
{
	return mPortrait.getHeight();
}
int Hero::getWidth()
{
	return mPortrait.getWidth();
}
