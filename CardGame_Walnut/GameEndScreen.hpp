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

	void render_Loss();
	void render_Win();

	void free();

private:
	DefaultTexture mVictory;
	DefaultTexture mLoss;

	Button mEndGameBtn;
};

