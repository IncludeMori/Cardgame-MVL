
#include "button.hpp"

#include "gMouse.hpp"

#include <iostream>

void Button::disable()
{
	setAlpha(75);
	isEnabled = false;
}

bool Button::IsPressed()
{
	if (isEnabled)
	{
		int mouse_y = gMouse.getY();
		int mouse_x = gMouse.getX();

		if (mouse_x > mPosX && mouse_x < mPosX + mWidth &&
			mouse_y > mPosY && mouse_y < mPosY + mHeight &&
			gMouse.isPressed() && gMouse.canPressBtn())
		{
			gMouse.setBtnPressed();
			return true;
		}
		else if (gMouse.isPressed())
		{
			return false;
		}
	}
	return false;
}

