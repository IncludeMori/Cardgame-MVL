#include "SetupPvp.hpp"

#include <iostream>
#include "gMouse.hpp"
#include "IPInfo.hpp"


bool isMouseEvent(SDL_Event &e)
{
	std::cout << "e:" << e.type << std::endl;
	if (e.type == SDL_MOUSEBUTTONDOWN)
		if (e.button.button == SDL_BUTTON_LEFT && e.button.clicks == 2)
			return true;
		else
			return false;

	return false;
}


enum {
	CREATE_SERVER = 0,
	CONNECT = 1
};
SetupPvp::SetupPvp()
{
	u.setPos(750, 300);


	int x = 680;
	int y = 450;

	mIsActive = true;
	mActiveField = 0;

	mButtonIsActive[CREATE_SERVER] = false;
	mButtonIsActive[CONNECT] = false;

	EnterIP.loadFromRenderedText("Server IP:");
	EnterPort.loadFromRenderedText("Server Port:");

	mCreateServBtn.loadFromFile("Data/createServer.png");
	mConnectBtn.loadFromFile("Data/connectServer.png");
	mBackBtn.loadFromFile("Data/back_arrow.png");
	mCreateServBtn.setPos(x+30, 350);
	mConnectBtn.setPos(x+330, 350);
	mBackBtn.setPos(x - 200, 450);

	mConnectToServer.loadFromFile("Data/connecttoserver.png");
	mConnectToServer.setPos(x + 200, 670);

	EnterIP.setPos(x - 100, y);
	EnterPort.setPos(x - 100, y+100);
	mIPInput.setPos(x+100,y);
	mPortInput.setPos(x + 150, y + 100);

	field1 = { x + 90,y,400,40 };
	field2 = { x + 157,y+100,150,40 };

}

void SetupPvp::update(SDL_Event &e)
{
	if (mBackBtn.IsPressed())
	{
		if (mButtonIsActive[CONNECT] || mButtonIsActive[CREATE_SERVER])
		{
			mButtonIsActive[CONNECT] = false;
			mButtonIsActive[CREATE_SERVER] = false;
		}
		else
			mIsActive = false;
	}

	if (mButtonIsActive[CONNECT])
	{
		mhandleInput.update(e);

		if (mActiveField == 0)
		{
			mIPInput.initText(mhandleInput.getMod());
		}
		else
			mPortInput.initText(mhandleInput.getMod());


		if (isMouseEvent(e))
		{
			if (gMouse.isInside(field1))
			{
				mActiveField = 0;
				mhandleInput.reset();
			}
			else if (gMouse.isInside(field2))
			{
				mActiveField = 1;
				mhandleInput.reset();
			}
		}
	}
	else if (mButtonIsActive[CREATE_SERVER])
	{

	}
	else if (mCreateServBtn.IsPressed())
	{
		mButtonIsActive[CREATE_SERVER] = true;
		mButtonIsActive[CONNECT] = false;
	}
	else if (mConnectBtn.IsPressed())
	{
		mButtonIsActive[CONNECT] = true;
		mButtonIsActive[CREATE_SERVER] = false;
	}

}

void SetupPvp::render()
{
	mBackBtn.render();

	if (mButtonIsActive[CREATE_SERVER])
	{
		u.render();
	}
	else if (mButtonIsActive[CONNECT])
	{
		EnterIP.render();
		EnterPort.render();
		mIPInput.renderText();
		mPortInput.renderText();

		mConnectToServer.render();

		drawRect(field1);
		drawRect(field2);
	}
	else
	{
		mCreateServBtn.render();
		mConnectBtn.render();
	}
}


bool SetupPvp::isActive()
{
	return mIsActive;
}
void SetupPvp::enable()
{
	mIsActive = true;
}
