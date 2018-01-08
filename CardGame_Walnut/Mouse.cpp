#include "Mouse.hpp"
#include <iostream>

Mouse::Mouse()
{
	update();
	mBtnPressed = false;
}

void Mouse::update()
{
	SDL_GetMouseState(&mPosX, &mPosY);

	if (mPosX < 0) { mPosX = 0; }
	if (mPosY < 0) { mPosY = 0; }

	mX_df = mPosX - mOldX;
	mY_df = mPosY - mOldY;

	mOldX = mPosX;
	mOldY = mPosY;
}

void Mouse::BtnDown()
{
	mBtnPressed = true;
}

void Mouse::BtnUp()
{
	mBtnPressed = false;
}

bool Mouse::isPressed()
{
	return mBtnPressed;
}

int Mouse::getX()
{
	return mPosX;
}

int Mouse::getY()
{
	return mPosY;
}

int Mouse::getX_df()
{
	return mX_df;
}
int Mouse::getY_df()
{
	return mY_df;
}