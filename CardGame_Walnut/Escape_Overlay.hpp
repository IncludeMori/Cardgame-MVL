#pragma once

#include "Button.hpp"
#include "gScreenSize.hpp"

class Escape_Overlay
{
public:
	Escape_Overlay();

	bool update();
	bool update(SDL_Event &e);

	void render();

	void setActive();
	void setInactive();

	bool isActive();

private:
	bool mKeyUp;
	bool mIsActive;

	DefaultTexture mQuestion;
	Button mYesBtn;
	Button mNoBtn;

};