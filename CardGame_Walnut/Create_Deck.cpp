#include "Create_Deck.hpp"

#include <iostream>
#include "sol\sol.hpp"
#include <vector>
#include "draw_collection.hpp"
#include "Save_Deck.hpp"
#include "gMouse.hpp"
#include "FPS_Timer.hpp"

#include "loadCards.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

Create_Deck::Create_Deck()
{
	hover_card = -1;
	loadAllCards();
	Deck_Saved = false;
	not_done = true;

	goBackBtn.loadFromFile("Data/back_btn.png");
	Deck_Size.loadFromFile("Data/deck_size.png");

	OkBtn.loadFromFile("Data/continue.png");
	tDeck_Saved.loadFromFile("Data/deck_saved.png");

	DeckSize = 0;
	Max_DeckSize = 30;

	saveDeck.loadFromFile("Data/savedeck.png");
	CardAdded = false;
	CardRemoved = false;

	mPath = "Save/player_deck.txt";

	mPage = 0;
	Max_Page = 3;

	leftT.loadFromFile("Data/left.png");
	right.loadFromFile("Data/right.png");



	DeckSizeSign.setPos(SCREEN_WIDTH / 2 + 400, 50);
	PageSign.setPos(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 12, 50);

	int sX = SCREEN_WIDTH / 2 + 300;
	int sY = 100;
	for (int i = 0; i < 30; i++)
	{
		mSmallPosX.push_back(sX);
		mSmallPosY.push_back(sY);

		sX += 120;

		if (sX >= SCREEN_WIDTH / 2 + 300 + 5 * 100)
		{
			sX = SCREEN_WIDTH / 2 + 300;
			sY = sY + 150;
		}


	}
}

Create_Deck::~Create_Deck()
{
	free();
}

bool Create_Deck::loop()
{
	Fps_Timer FpsTimer; // init & start fps timer

	while (!QuitGame)
	{


		//if (key[SDL_SCANCODE_ESCAPE])
		//{
		//	std::cout << "lololol";
		//}


		FpsTimer.startFrame();
		FpsTimer.calcFps();

		if (!update())
			QuitGame = true;

		SDL_RenderClear(Renderer.get()); //clear screen
		render();

		SDL_RenderPresent(Renderer.get()); // update screen

		FpsTimer.endFrame();
	} // main loop 

	return false;
}

bool Create_Deck::update()
{
	gMouse.update();

	SDL_PollEvent(&e);
	EventHandler.handleEvent(e);

	// user is creating deck
	if (!Deck_Saved)
	{
		if (!gMouse.isPressed())
		{
			CardAdded = false;
			CardRemoved = false;

			//check if mouse is over collection_card
			if (gMouse.getX() > SCREEN_WIDTH / 2)
			{

				for (unsigned int i = 0; i < mCurrentDeckCards.size(); i++)
				{
					int j = 0;
					if (mCurrentDeckCards[i]->MouseIsAbove())
					{
						std::string name = mCurrentDeckCards[i]->getName();


						bool x = false;

						while (!x)
						{
							if (j == mCards.size())
							{

								x = true;
								hover_card = -1;
							}
							else if (name == mCards[j]->getName())
							{
								x = true;
								hover_card = j;

							}
							else
								j++;


						}
					}
					if (j == mCards.size() || j == 0)
						hover_card = -1;
				}


			}



		}
		else
		{
			//user wants to go back
			if (goBackBtn.IsPressed())
			{
				not_done = false;
				std::cout << "back";
			}
			else if (saveDeck.IsPressed())
			{
				if (fsaveDeck() == true)
				{
					SDL_Delay(1000);
					Deck_Saved = true;

					Uint8 alpha = 50;
					saveDeck.setAlpha(alpha);
					leftT.setAlpha(alpha);
					right.setAlpha(alpha);


					for (unsigned int i = 0; i < mCurrentDeckCards.size(); i++)
					{
						if (mCurrentDeckCards[i] != nullptr)
						{
							mCurrentDeckCards[i]->setAlpha(alpha);
						}
					}
					int test = mPage * 15;
					for (unsigned int i = test; i < mCards.size(); i++)
					{
						//mCards[i]->setPos(mPosX[i] - mCam.getPosX(), mPosY[i]);

						//if (mCam.isInside(mCards[i]->getX(), mCards[i]->getY(), mCards[i]->getWidth(), mCards[i]->getHeight()))
						//{
						if (i < (mPage + 1) * 15)
						{
							mCards[i]->setAlpha(alpha);


						}
					}

				}

			}
			//Change page
			else if (right.IsPressed())
			{
				std::cout << "right";
				mPage++;
				if (mPage > Max_Page)
					mPage--;
				else
					PageSign.increase(1);

				SDL_Delay(500);
			}
			else if (leftT.IsPressed())
			{
				std::cout << "left";
				mPage--;
				if (mPage < 0)
					mPage++;
				else
					PageSign.increase(-1);

				SDL_Delay(500);
			}
			//----------------------------


			int test = mPage * 15;

			if (CardAdded == false && DeckSize + 1 <= Max_DeckSize)
			{
				for (unsigned int i = test; i < mCards.size(); i++)
				{
					if (i < (mPage + 1) * 15)
					{
						if (mCards[i]->MouseIsAbove() && gMouse.isPressed())
						{
							std::cout << "Name:" << mCards[i]->getName();
							std::string y = mCards[i]->getName();
							mCurrentDeckCards.push_back(std::unique_ptr<Collection_Card>(new Collection_Card(y)));
							mCurrentDeckCards[mCurrentDeckCards.size() - 1]->loadTexture();
							mCurrentDeckCards[mCurrentDeckCards.size() - 1]->setPos(mSmallPosX[mCurrentDeckCards.size() - 1], mSmallPosY[mCurrentDeckCards.size() - 1]);
							std::cout << "Added:" << mCards[i]->getName() << std::endl;
							CardAdded = true;
							DeckSize++;
							DeckSizeSign.increase(1);
						}
					}

				}
			}


			//remove cards from deck
			if (!CardRemoved)
			{
				unsigned int i = 0;
				bool added = false;
				while (i < mCurrentDeckCards.size() && !added)
				{


					if (mCurrentDeckCards[i] != nullptr)
					{
						if (mCurrentDeckCards[i]->MouseIsAbove() && gMouse.isPressed())
						{
							std::cout << "Removed:" << i << std::endl;
							mCurrentDeckCards[i].reset();
							DeckSizeSign.increase(-1);
							DeckSize--;
							mCurrentDeckCards.erase(mCurrentDeckCards.begin() + i);
							added = true;
							//std::cout << "Size:" << mCurrentDeckCards.size() << std::endl;
						}
					}
					i++;

				}
				int j = 0;
				//update current Deck position
				for (mIt = mCurrentDeckCards.begin(); mIt != mCurrentDeckCards.end(); mIt++)
				{
					mCurrentDeckCards[j]->setPos(mSmallPosX[j], mSmallPosY[j]);
					j++;
				}
				CardRemoved = true;
			}






		}
	}
	else
	{
		if (OkBtn.IsPressed())
		{
			not_done = false;
		}
	}

	return not_done;
}

void Create_Deck::render()
{
	goBackBtn.render();
	int test = mPage * 15;
	Deck_Size.render();


	for (unsigned int i = 0; i < mCurrentDeckCards.size(); i++)
	{
		if (mCurrentDeckCards[i] != nullptr)
		{
			mCurrentDeckCards[i]->render();
		}
	}

	for (unsigned int i = test; i < mCards.size(); i++)
	{
		//mCards[i]->setPos(mPosX[i] - mCam.getPosX(), mPosY[i]);

		//if (mCam.isInside(mCards[i]->getX(), mCards[i]->getY(), mCards[i]->getWidth(), mCards[i]->getHeight()))
		//{
		if (i < (mPage + 1) * 15)
		{
			mCards[i]->render();


		}
	}

	//Hilfslinien
	drawCardField();
	drawDeckField();


	if (Deck_Saved)
	{
		tDeck_Saved.render();
		OkBtn.render();
	}


	saveDeck.render();
	DeckSizeSign.render();
	PageSign.render();
	leftT.render();
	right.render();

	/*
	//render hover_card
	if (hover_card != -1)
	{
	mCards[hover_card]->setPos(SCREEN_WIDTH / 2 - mCards[hover_card]->getWidth(), SCREEN_HEIGHT / 2 - mCards[hover_card]->getHeight());
	mCards[hover_card]->render();
	mCards[hover_card]->setPos(mPosX[hover_card % 15], mPosY[hover_card % 15]);
	}*/
}

bool Create_Deck::createDeck()
{
	update();
	render();

	return not_done;

}

void Create_Deck::updatePos()
{
	int x = 190;
	int y = 130;

	int sX = x, sY = y;
	for (int i = 0; i < 5 * 3; i++)
	{
		mPosX.push_back(x);
		mPosY.push_back(y);

		x = x + sX;

		if (x == sX * 6)
		{
			x = sX;
			y = y + 2.5*sY;
		}
	}
}

void Create_Deck::loadAllCards()
{
	loadCards ExistingCards;
	ExistingCards.load(mCards);

	updatePos();
	int x = 0;
	for (unsigned int i = 1; i <= mCards.size(); i++)
	{
		if (i % 15 == 0)
			Max_Page++;

		mCards[i - 1]->setPos(mPosX[x], mPosY[x]);
		x++;
		if (x > 14) { x = 0; }
	}
}

bool Create_Deck::fsaveDeck()
{
	if (DeckSize == 30)
	{
		for (unsigned int i = 0; i < mCurrentDeckCards.size(); i++)
		{
			mDeck += mCurrentDeckCards[i]->getName() + "0";
		}
		Save_Deck save;
		save.save(mDeck, 0);
		std::cout << "Deck saved..." << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void Create_Deck::free()
{

}
