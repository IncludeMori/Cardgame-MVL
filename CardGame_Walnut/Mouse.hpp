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

	int getX(); 
	int getY();

	//difference since last frame
	int getX_df(); 
	int getY_df(); 

private:
	int mPosX, mPosY;

	int mOldX, mOldY;
	int mX_df, mY_df;

	bool mBtnPressed;
	bool WheelUp, WheelDown;
};