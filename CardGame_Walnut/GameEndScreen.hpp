#pragma once

#include "DefaultTexture.hpp"
#include "Button.hpp"

#include "gScreenSize.hpp"

class GameEndScreen
{
public:
	GameEndScreen();
	~GameEndScreen();

	bool update();

	void renderLoss();
	void renderWin();

	void free();

private:
	DefaultTexture mVictory;
	DefaultTexture mLoss;

	Button mEndGameBtn;
};

