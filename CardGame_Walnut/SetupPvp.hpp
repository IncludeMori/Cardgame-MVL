#pragma once

#include "InputField.hpp"
#include "Button.hpp"
#include "TTF_Text.hpp"

class SetupPvp
{
public:
	SetupPvp();

	void update();
	void render();

	bool isActive();
	void enable();

private:
	bool mIsActive;

	Button mCreateServBtn, mConnectBtn, mBackBtn;

	TTF_Text mHostIP; //local host ip
	//InputField mInputIP; //

	Text mIPInput;

};