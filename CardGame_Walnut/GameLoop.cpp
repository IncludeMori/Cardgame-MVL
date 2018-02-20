#include "GameLoop.hpp"

#include "gQuit.hpp"
#include "FPS_Timer.hpp"
#include "MenuBtn_Enum.hpp"
#include "Sub_Btn_Enum.hpp"

#include "Escape_Overlay.hpp"
#include "Create_Deck.hpp"

#include "LoadingScreen.hpp"

#include <time.h>
#include <chrono>
#include <thread>


GameClass::GameClass()
{
}
bool GameClass::main_loop()
{
	//test
	std::cout << "one";
	//LoadingScreen loadScreen;
	std::cout << "two";

	mCurrentlyActive = Btn_Type::VS_AI;

	while (!gQuitGame)
	{

		//DELETE TO ENABLE MENU
		//ALSO: delete gQuitGame = true inside VS_AI
		/*
		loadScreen.start();
		mMenu.reset(new Menu());
		loadScreen.end();
		if (!mMenu->loop()) //Menu wird beendet wenn ein Btn gedrückt wird
			mCurrentlyActive = mMenu->activeBtn(); //gedrückten Button abfragen

		mMenu->free();
		mMenu.release();
		*/
		if (gQuitGame == false)
		{
			switch (mCurrentlyActive)
			{
				//start actual game
			case(Btn_Type::VS_AI):
				//loadScreen.start();
				mGame.reset(new Game());
				//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
				//loadScreen.end();
				if (!mGame->loop()) {
					mGame->free();
					mGame.release();
					mCurrentlyActive = Btn_Type::ERROR;

					//DELETE!!!!!!!
					gQuitGame = true;
				}
				break;
				//go to-> collection menu
			case(Btn_Type::CREATE_DECK):
				//loadScreen.start();
				mCreateDeck.reset(new Create_Deck());
				//loadScreen.end();
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
