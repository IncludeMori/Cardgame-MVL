#pragma once

#include "InputField.hpp"
#include "Button.hpp"
#include "TTF_Text.hpp"
#include "InputHandler.hpp"

#include "draw.hpp"

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
	Button mConnectToServer;

	TTF_Text mHostIP; //local host ip
	TTF_Text EnterIP,EnterPort;
	//InputField mInputIP; //

	Text mIPInput,mPortInput;
	InputHandler mhandleInput;

	bool mButtonIsActive[2];

	SDL_Rect field1, field2;
	int mActiveField;

};