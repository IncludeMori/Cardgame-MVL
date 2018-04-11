#include "Menu.hpp"
#include "draw.hpp"

#include <iostream>
#include "gMouse.hpp"
#include "gQuit.hpp"
#include "display_text.hpp"


Menu::Menu()
{
	initBtns();
}
Menu::~Menu()
{
	free();
}

bool Menu::loop()
{
	FpsTimer.start();

	while (!QuitGame)
	{
		FpsTimer.startFrame();


		if (!update())
			QuitGame = true;

		SDL_RenderClear(gRenderer); //clear screen
		render();

		SDL_RenderPresent(gRenderer); // update screen

		FpsTimer.calcFps(); //
		FpsTimer.endFrame();
	} // main loop 
	
	return false;
}
bool Menu::update()
{

	gMouse.update();
	SDL_PollEvent(&e);
		
	/*
	SDL_Keymod Keymod = SDL_GetModState();
	//e.key.keysym.mod
	if (e.key.type == SDL_KEYDOWN)
	{

		int Scancode = e.key.keysym.scancode;

		if (Scancode = SDLK_1)
		{
			mActiveSubBtn = Btn_Type::VS_PLAYER; PvpMenu.enable();
		}

	}*/


	if (Esc_Overlay.update(e))
	{
		gQuitGame = true;
	    return false;
	}

	int x = EventHandler.handleEvent(e);

	if (mActiveSubBtn == Btn_Type::VS_PLAYER && !Esc_Overlay.isActive())
	{
		if (!PvpMenu.isActive())
			mActiveSubBtn = Btn_Type::ERROR;
		else
			PvpMenu.update(e);
	}
	else if (!Esc_Overlay.isActive())
	{
		if (x != 0)
		{
			switch (mActiveButton)
			{
			case(PLAY_BTN):
				if (mSubButton[static_cast<int>(Btn_Type::VS_PLAYER)].IsPressed()) { mActiveSubBtn = Btn_Type::VS_PLAYER; PvpMenu.enable(); }
				else if (mSubButton[static_cast<int>(Btn_Type::VS_AI)].IsPressed()) { mActiveSubBtn = Btn_Type::VS_AI; }
				break;
			case(COLLECTION_BTN):
				if (mSubButton[static_cast<int>(Btn_Type::CREATE_DECK)].IsPressed()) { mActiveSubBtn = Btn_Type::CREATE_DECK; }
				else if (mSubButton[static_cast<int>(Btn_Type::SHOW_CARDS)].IsPressed()) { mActiveSubBtn = Btn_Type::SHOW_CARDS; }
				break;
			case(OPTIONS_BTN):
				if (mSubButton[4].IsPressed()) { mActiveSubBtn = Btn_Type::START_STUDIO; }
			}

			if (mButtons[PLAY_BTN].isPressed()) {

				if (mActiveButton != PLAY_BTN)
				{
					
					mButtons[mActiveButton].setInactive();
					mActiveButton = PLAY_BTN;
				}

			}
			else if (mButtons[COLLECTION_BTN].isPressed())
			{
				if (mActiveButton != COLLECTION_BTN)
				{
					mButtons[mActiveButton].setInactive();
					mActiveButton = COLLECTION_BTN;
				}
			}
			else if (mButtons[OPTIONS_BTN].isPressed())
			{
				if (mActiveButton != OPTIONS_BTN)
				{
					mButtons[mActiveButton].setInactive();
					mActiveButton = OPTIONS_BTN;
				}
			}
			else if (mButtons[CREDITS_BTN].isPressed())
			{
				if (mActiveButton != CREDITS_BTN)
				{
					mButtons[mActiveButton].setInactive();
					mActiveButton = CREDITS_BTN;
				}
			}
		}


	}


	Music.update();


	if (mActiveSubBtn != Btn_Type::ERROR && mActiveSubBtn != Btn_Type::VS_PLAYER)
		return false;

	return true;
}
void Menu::render()
{
	mButtons[PLAY_BTN].render();
	mButtons[COLLECTION_BTN].render();
	mButtons[OPTIONS_BTN].render();
	mButtons[CREDITS_BTN].render();

	switch (mActiveButton)
	{
	case(PLAY_BTN):
		if (mActiveSubBtn == Btn_Type::VS_PLAYER)
		{
			PvpMenu.render();
		}
		else
		{
			mSubButton[0].render();
			mSubButton[1].render();
		}
		break;
	case(COLLECTION_BTN):
		mSubButton[2].render();
		mSubButton[3].render();
		break;
	case(OPTIONS_BTN):
		mSubButton[4].render();
		break;
	}


	if (Esc_Overlay.isActive())
		Esc_Overlay.render();

	drawRect(rect);

	Music.render();

	FpsTimer.render();

	
}

bool Menu::isActive()
{
	return mIsActive;
}
void Menu::setInactive()
{
	mIsActive = false;
	free();
}
bool Menu::setActive()
{
	if (mIsActive == false)
	{

		mIsActive = true;
		if (
			mButtons[PLAY_BTN].isEmpty() &&
			mButtons[COLLECTION_BTN].isEmpty() &&
			mButtons[OPTIONS_BTN].isEmpty() &&
			mButtons[CREDITS_BTN].isEmpty()
			)
		{
			if (initBtns())
				return true;

			return false;

		}
		else
			return false;
	}
	return false;
}

Btn_Type Menu::activeBtn()
{
	if (mActiveSubBtn == Btn_Type::VS_PLAYER || mActiveSubBtn == Btn_Type::VS_AI)
		Music.stop();
	return mActiveSubBtn;
}

void Menu::reset()
{
	QuitGame = false;
	mActiveSubBtn = Btn_Type::ERROR;
}

void Menu::free()
{
	mButtons[mActiveButton].setInactive();
	mButtons[PLAY_BTN].free();
	mButtons[COLLECTION_BTN].free();
	mButtons[OPTIONS_BTN].free();
	mButtons[CREDITS_BTN].free();

	
}


bool Menu::initBtns()
{
	mSubButton[static_cast<int>(Btn_Type::VS_PLAYER)].loadFromFile("Data/pvp_btn.png");
	mSubButton[static_cast<int>(Btn_Type::VS_AI)].loadFromFile("Data/pve_btn.png");

	mSubButton[static_cast<int>(Btn_Type::CREATE_DECK)].loadFromFile("Data/create_deck_btn.png");
	mSubButton[static_cast<int>(Btn_Type::SHOW_CARDS)].loadFromFile("Data/show_cards_btn.png");
	

	mSubButton[4].loadFromFile("Data/Btn/startStudio.png");
	mSubButton[4].setPos(SCREEN_WIDTH / 2 - mSubButton[4].getWidth() / 2+300, SCREEN_HEIGHT / 2 - mSubButton[4].getHeight() / 2 +150);

	mSubButton[static_cast<int>(Btn_Type::VS_PLAYER)].setPos(SCREEN_WIDTH / 2 - 1.25*mSubButton[0].getWidth(), SCREEN_HEIGHT / 3);
	mSubButton[static_cast<int>(Btn_Type::VS_AI)].setPos(SCREEN_WIDTH / 2 + 0.25*mSubButton[0].getWidth(), SCREEN_HEIGHT / 3);

	mSubButton[static_cast<int>(Btn_Type::CREATE_DECK)].setPos(SCREEN_WIDTH / 2 - 1.25*mSubButton[0].getWidth(), SCREEN_HEIGHT / 3);
	mSubButton[static_cast<int>(Btn_Type::SHOW_CARDS)].setPos(SCREEN_WIDTH / 2 + 0.25*mSubButton[0].getWidth(), SCREEN_HEIGHT / 3);


	mActiveButton = PLAY_BTN;
	mButtons[mActiveButton].setActive();
	mActiveSubBtn = Btn_Type::ERROR;

	mButtons[PLAY_BTN].loadFromFile("Data/play_t.png");
	mButtons[COLLECTION_BTN].loadFromFile("Data/collection_t.png");
	mButtons[OPTIONS_BTN].loadFromFile("Data/options_t.png");
	mButtons[CREDITS_BTN].loadFromFile("Data/credits_t.png");

	//set start position
	int Y_POSITION = SCREEN_HEIGHT / 6;
	int X_POSITION = SCREEN_WIDTH / 2 - 2 * (mButtons[PLAY_BTN].getWidth());

	rect = { X_POSITION,Y_POSITION,mButtons[PLAY_BTN].getWidth() * 4,600 };

	//Set position
	mButtons[PLAY_BTN].setPos(X_POSITION, Y_POSITION);
	X_POSITION += mButtons[PLAY_BTN].getWidth();


	mButtons[COLLECTION_BTN].setPos(X_POSITION, Y_POSITION);
	X_POSITION += mButtons[PLAY_BTN].getWidth();

	mButtons[OPTIONS_BTN].setPos(X_POSITION, Y_POSITION);
	X_POSITION += mButtons[PLAY_BTN].getWidth();

	mButtons[CREDITS_BTN].setPos(X_POSITION, Y_POSITION);

	//mSubButton[static_cast<int>(Btn_Type::VS_PLAYER)].disable();
	mButtons[CREDITS_BTN].disable();
	mSubButton[static_cast<int>(Btn_Type::SHOW_CARDS)].disable();

	
	// check if buttons != empty
	if (mButtons[PLAY_BTN].isEmpty() ||
		mButtons[COLLECTION_BTN].isEmpty() ||
		mButtons[OPTIONS_BTN].isEmpty() ||
		mButtons[CREDITS_BTN].isEmpty()
		)
		return false;

	return true;
}