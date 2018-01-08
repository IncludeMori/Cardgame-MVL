
#include "button.hpp"

#include "gRenderer.hpp"
#include "gMouse.hpp"

#include <iostream>

Button::Button()
{
	isEnabled = true;
}
Button::Button(int x, int y)
{
	mPosX = x;
	mPosY = y;
}
Button::~Button()
{
	free();
}

void Button::update()
{

}

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
			gMouse.isPressed())
		{
			std::cout << "T";
			return true;
		}
		else if (gMouse.isPressed())
		{
			std::cout << "F";
			return false;
		}
	}
	return false;
}

