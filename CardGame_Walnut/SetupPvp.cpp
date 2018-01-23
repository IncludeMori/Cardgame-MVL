#include "SetupPvp.hpp"

#include <iostream>

SetupPvp::SetupPvp()
{
	int x = 680;

	mIsActive = true;

	mCreateServBtn.loadFromFile("Data/createServer.png");
	mConnectBtn.loadFromFile("Data/connectServer.png");
	mBackBtn.loadFromFile("Data/back_arrow.png");
	mCreateServBtn.setPos(x+30, 350);
	mConnectBtn.setPos(x+330, 350);
	mBackBtn.setPos(x - 170, 450);

	mIPInput.setPos(400, 10);

}

void SetupPvp::update(SDL_Event &e)
{
	
	if (mBackBtn.IsPressed())
	{
		//mIsActive = false;
	}
	else if (mCreateServBtn.IsPressed())
	{
		//show own ip
		//[waiting for opponent....]
		//
	}
	else if (mConnectBtn.IsPressed())
	{
		connectIsActive = true;
	}

	if (connectIsActive)
	{
		mhandleInput.update(e);
		mIPInput.initText(mhandleInput.getMod());
	}
}

void SetupPvp::render()
{
	if (mBackBtn.IsPressed())
	{
		mIsActive = false;
	}
	else if (mCreateServBtn.IsPressed())
	{
		//show own ip
		//[waiting for opponent....]
		//
	}
	else if (mConnectBtn.IsPressed())
	{
		connectIsActive = true;
	}

	if (connectIsActive)
	{
		mIPInput.renderText();
	}
	else
	{
		mCreateServBtn.render();
		mConnectBtn.render();
		mBackBtn.render();
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
