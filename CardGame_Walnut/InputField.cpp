#include "InputField.hpp"



InputField::InputField()
{
}

InputField::InputField(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

InputField::InputField(int x, int y, int w, int h)
{
	mWidth = w;
	mHeight = h;
	
	mShowText.setPos(x, y);
}
