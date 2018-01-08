#pragma once

#include "Button.hpp"

class Menu_Button : public Button
{
public:
	Menu_Button();

	bool loadFromFile(std::string path);

	void render();

	void setPos(int x, int y);


	bool isPressed();
	bool isActive();

	void setInactive();
	void setActive();

	void free();
private:
	DefaultTexture mBorder;

	bool mIsActive;

};