#include "GameLoop.hpp"

#include "gQuit.hpp"
#include "FPS_Timer.hpp"
#include "MenuBtn_Enum.hpp"
#include "Sub_Btn_Enum.hpp"

#include "Escape_Overlay.hpp"
#include "Create_Deck.hpp"

#include "LoadingScreen.hpp"

GameClass::GameClass()
{
}
bool GameClass::main_loop()
{
	//test
	LoadingScreen loadScreen;

	while (!gQuitGame)
	{
		mMenu.reset(new Menu());
		if (!mMenu->loop()) //Menu wird beendet wenn ein Btn gedrückt wird
			mCurrentlyActive = mMenu->activeBtn(); //gedrückten Button abfragen

		mMenu->free();
		mMenu.release();

		if (gQuitGame == false)
		{
			switch (mCurrentlyActive)
			{
				//start actual game
			case(Btn_Type::VS_AI):
				loadScreen.start();
				mGame.reset(new Game());
				loadScreen.end();
				if (!mGame->loop()) {
					mGame->free();
					mGame.release();
					mCurrentlyActive = Btn_Type::ERROR;
				}
				break;
				//go to-> collection menu
			case(Btn_Type::CREATE_DECK):
				loadScreen.start();
				mCreateDeck.reset(new Create_Deck());
				loadScreen.end();
				if (!mCreateDeck->loop())
				{
					mCreateDeck->free();
					mCreateDeck.release();
					mCurrentlyActive = Btn_Type::ERROR;
				}
				break;
			case(Btn_Type::START_STUDIO):
				std::cout << std::endl;
				system("test.bat");
				break;
			}
			//danach wird das Menu wieder aufgerufen-> schleife fängt von vorne an
		}





	} // main loop 

	return true;
}
