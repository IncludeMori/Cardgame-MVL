#include "GameEndScreen.hpp"



GameEndScreen::GameEndScreen()
{
	mVictory.loadFromFile("Data/victory.png");
	mLoss.loadFromFile("Data/loss.png");
	mEndGameBtn.loadFromFile("Data/Continue.png");

	mVictory.setPos(SCREEN_WIDTH / 2 - mVictory.getWidth() / 2, SCREEN_HEIGHT / 2 - mVictory.getHeight() / 2);
	mLoss.setPos(SCREEN_WIDTH / 2 - mVictory.getWidth() / 2, SCREEN_HEIGHT / 2 - mVictory.getHeight() / 2);
	mEndGameBtn.setPos(mVictory.getPosX() + mVictory.getWidth()/2-mEndGameBtn.getWidth()/2, mVictory.getPosY() + 125);
}


GameEndScreen::~GameEndScreen()
{
}

bool GameEndScreen::update()
{
	if (mEndGameBtn.IsPressed())
	{
		return false;
	}
	return true;
}

void GameEndScreen::render_Loss()
{
	mEndGameBtn.render();
	mLoss.render();
}
void GameEndScreen::render_Win()
{
	mEndGameBtn.render();
	mVictory.render();
}

void GameEndScreen::free()
{
	
}
