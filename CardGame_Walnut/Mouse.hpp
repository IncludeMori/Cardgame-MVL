//
// @Author: Moritz Volkenandt (2016-)
//
// Used for: handling mouse data
//
#pragma once

#include <SDL.h>

class Mouse
{
public:
	Mouse();
	
	void update(); //updates position & current status

	void BtnDown();
	void BtnUp();
	bool isPressed(); // return true if btn is down --- rename
	bool canPressBtn();

	int getX(); 
	int getY();

	//difference since last frame
	int getX_df(); 
	int getY_df(); 

	bool isInside(SDL_Rect &rect);

	void setBtnPressed();

private:
	int mPosX, mPosY;

	int mOldX, mOldY;
	int mX_df, mY_df;

	bool mLeftMouseBtnPressed;
	bool WheelUp, WheelDown;

	bool mCanPressBtn;

};