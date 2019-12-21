
#include "Game.hpp"
#include "gMouse.hpp"
#include "FPS_Timer.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

Game::Game()
{
	keyUp = true;
	QuitGame = false;
	init();
	//MPlayerField->setHero(mOppHero);
	mBackground.loadFromFile("Data/background/background.png");
}
Game::~Game()
{

}

bool Game::loop()
{
	FpsTimer.start();
	while (!QuitGame)
	{
		FpsTimer.startFrame();

		if (!update())
			QuitGame = true;

		//Update screen
		SDL_RenderClear(Renderer.get());
		render();
		SDL_RenderPresent(Renderer.get());

		FpsTimer.calcFps();
		FpsTimer.endFrame();

		
	} 
	QuitGame = false;
	return false;
}

bool Game::update()
{
	SDL_PollEvent(&mCurrentEvent);
	EventHandler.handleEvent(mCurrentEvent);
	gMouse.update();

	//----------------------------------------------------------------------------------------------------------
	if (mOpponent->isAlive() && mPlayer->isAlive())
	{
		static bool alpha_reset = false;
		/*
		if (!mOpponent->isAlive() && !mMenu.isActive())
		{
		mMenu.setActive();
		}
		*/
		

		//Check if Player wants to quit the game
		if (Esc_Overlay.update(mCurrentEvent) == true) 
			return false;

		if (!Esc_Overlay.isActive())
		{
			if (alpha_reset == false)
			{
				mOpponent->setAlpha(255);
				mPlayer->setAlpha(255);
				mTurn->setAlpha(255);
				alpha_reset = true;
			}

			mOpponent->update();
			mTurn->update();

			if (mTurn->isPlayersTurn() == true)
			{
				if (mPlayer->update())
				{
					mTurn->deactivate(); //deaktiviert alle Buttons
				}
				else
				{
					mTurn->activate();
				}
			}
			else {
				mOpponent->play();
			}

			return true;
		}
		else //ESC Overlay active
		{

			if (alpha_reset == true)
			{
				mOpponent->setAlpha(60);
				mPlayer->setAlpha(60);
				mTurn->setAlpha(60);
				alpha_reset = false;
			}
			return true;
		}
	} 
	//----------------------------------------------------------------------------------------------------------
	else //someone is dead [END]
	{
		mOpponent->setAlpha(60);
		mPlayer->setAlpha(60);
		mTurn->setAlpha(60);

		if (!mPlayer->isAlive())
		{

		}
		else if (!mOpponent->isAlive())
		{

		}
		return End_Screen.update();
	}
}

void Game::render()
{
	mBackground.render();
	mTurn->render();
	mOpponent->render();
	mPlayer->render();
	drawLines(); //dev test

	if (!mPlayer->isAlive())
	{
		End_Screen.renderLoss();
	}
	else if (!mOpponent->isAlive())
	{
		End_Screen.renderWin();
	}

	if (Esc_Overlay.isActive())
		Esc_Overlay.render();

	//FpsTimer.render();
}


void Game::init()
{
	mBackground.loadFromFile("Data/Background/background.png");
	mBackground.setPos(0, 0);

	mPlayer.reset(new Player());
	mOpponent.reset(new Opponent());

	mPlayer->setField(mOpponent->getField());
	mPlayer->setHero(mOpponent->getHero());

	mOpponent->setField(mPlayer->getField());
	mOpponent->setHero(mPlayer->getHero());

	mTurn.reset(new CurrentTurn(who::type::PLAYER, mPlayer, mOpponent));
}

void Game::free()
{
	//End_Screen.free();

	mPlayer->free();
	mOpponent->free();
	
	mPlayer.reset();
	mOpponent.reset();
	mTurn.reset();
}