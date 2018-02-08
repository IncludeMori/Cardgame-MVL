#include "Mouse.hpp"
#include <iostream>

Mouse::Mouse()
{
	update();
	mLeftMouseBtnPressed = false;
	mCanPressBtn = false;
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
	if (!mLeftMouseBtnPressed)
	{
		mCanPressBtn = true;
		
	}
	mLeftMouseBtnPressed = true;
}

void Mouse::BtnUp()
{
	mLeftMouseBtnPressed = false;
	mCanPressBtn = false;
}

bool Mouse::isPressed()
{
	return mLeftMouseBtnPressed;
}
bool Mouse::canPressBtn()
{
	return mCanPressBtn;
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

bool Mouse::isInside(SDL_Rect & rect)
{
	if (mPosX > rect.x && mPosY > rect.y && mPosX < rect.x + rect.w && mPosY < rect.y + rect.h)
		return true;
	else
		return false;
}

void Mouse::setBtnPressed()
{
	mCanPressBtn = false;
}