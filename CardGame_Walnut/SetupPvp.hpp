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

private:
	Button mCreateServBtn, mConnectBtn;

	TTF_Text mHostIP; //local host ip
	InputField mInputIP; //

};