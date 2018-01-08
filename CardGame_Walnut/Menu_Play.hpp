//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: handles menu button interaction
//
#pragma once

#include <vector>

#include "Menu_Button.hpp"

class Menu_Play
{
public:
	Menu_Play();

	void update();
	void render();

	void free();

private:

	Menu_Button mMainButton;
	std::vector<Button> mButtons;
};