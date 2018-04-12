#include "Menu_Button.hpp"

#include <iostream>
Menu_Button::Menu_Button()
{
	mIsActive = false;
}

bool Menu_Button::loadFromFile(std::string path)
{
	mBorder.loadFromFile("Data/menu_btn_border.png");

	Button::loadFromFile(path);
	return true;
	
}
void Menu_Button::render()
{
	Button::render();
	if (mIsActive) { mBorder.render(); }
}

void Menu_Button::setInactive()
{
	mIsActive = false;
}
void Menu_Button::setActive()
{
	mIsActive = true;
}
void Menu_Button::setPos(int x, int y)
{
	Button::setPos(x, y);
	mBorder.setPos(getPosX(), getPosY() + getHeight() - mBorder.getHeight());
}
bool Menu_Button::isPressed()
{
	bool pressed = Button::IsPressed();
	

	if (pressed)
		mIsActive = true;

	return pressed;
}


bool Menu_Button::isActive()
{
	return mIsActive;
}

void Menu_Button::free()
{
	
}