
#include "Game.hpp"
#include "gMouse.hpp"
#include "FPS_Timer.hpp"

Game::Game()
{
	keyUp = true;
	Init();
	//MPlayerField->setHero(mOppHero);
	mBackground.loadFromFile("Data/background/background.png");
}
Game::~Game()
{

}

bool Game::loop()
{
	Fps_Timer FpsTimer; // init & start fps timer
	float fps;
	static int counter = 0;
	while (!QuitGame)
	{


		//if (key[SDL_SCANCODE_ESCAPE])
		//{
		//	std::cout << "lololol";
		//}


		FpsTimer.start();
		fps = FpsTimer.calcFps();
		
		counter++;
		if (counter > 1000)
		{
			std::cout << "Fps:" << fps << std::endl;
			counter = 0;
		}


		if (!update())
			QuitGame = true;

		SDL_RenderClear(gRenderer); //clear screen
		render();

		SDL_RenderPresent(gRenderer); // update screen

		FpsTimer.endFrame();

		
	} // main loop 
	QuitGame = false;
	return false;
}

bool Game::update()
{
	SDL_PollEvent(&e);
	EventHandler.handleEvent(e);

	gMouse.update();

	//----------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------
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
		


		if (Esc_Overlay.update(e) == true) // player wants to quit game?
			return false;

		if (!Esc_Overlay.isActive())
		{


			if (alpha_reset == false)
			{
				mOpponent->setAlpha(255);
				mPlayer->setAlpha(255);
				mTurn->setAlpha(255);
				std::cout << "reset...............";
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
		else
		{

			if (alpha_reset == true)
			{
				mOpponent->setAlpha(60);
				mPlayer->setAlpha(60);
				mTurn->setAlpha(60);
				alpha_reset = false;
				std::cout << "Set Alpha...60..";
			}
			return true;
		}
	} //----------------------------------------------------------------------------------------------------------
	  //----------------------------------------------------------------------------------------------------------
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
	// return false(?)
}

void Game::render()
{
	mBackground.render();

	mTurn->render();
	mOpponent->render();
	mPlayer->render();
	drawLines();

	if (!mPlayer->isAlive())
	{
		End_Screen.render_Loss();
	}
	else if (!mOpponent->isAlive())
	{
		End_Screen.render_Win();
	}

	if (Esc_Overlay.isActive())
		Esc_Overlay.render();


}


void Game::Init()
{
	mBackground.loadFromFile("Data/Background/background01.png");
	mBackground.setPos(0, 0);

	mPlayer.reset(new Player());
	mOpponent.reset(new Opponent());

	mPlayer->setField(mOpponent->getField());
	mPlayer->setHero(mOpponent->getHero());

	mOpponent->setField(mPlayer->getField());
	mOpponent->setHero(mPlayer->getHero());

	mTurn.reset(new CurrentTurn(PLAYER, mPlayer, mOpponent));
}

void Game::free()
{

	//End_Screen.free();
	mBackground.free();

	mTurn->free();
	mPlayer->free();
	mOpponent->free();
	

	mPlayer.reset();
	mOpponent.reset();
	mTurn.reset();
}