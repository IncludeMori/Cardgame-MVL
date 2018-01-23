#pragma once

#include "InputField.hpp"
#include "Button.hpp"
#include "TTF_Text.hpp"
#include "InputHandler.hpp"

class SetupPvp
{
public:
	SetupPvp();

	void update(SDL_Event &e);
	void render();

	bool isActive();
	void enable();

private:
	bool mIsActive;

	Button mCreateServBtn, mConnectBtn, mBackBtn;

	TTF_Text mHostIP; //local host ip
	//InputField mInputIP; //

	Text mIPInput;
	InputHandler mhandleInput;

	bool connectIsActive = false;

};