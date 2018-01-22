//
// @Author: Moritz Volkenandt 
//
// Used for: main menu
//
#pragma once

#include "Menu_Button.hpp"
#include "gScreenSize.hpp"
#include "Click_EventHandler.hpp"

#include "MenuBtn_Enum.hpp"
#include "Main_Btn_Enum.hpp"
#include "Sub_Btn_Enum.hpp"

#include "Escape_Overlay.hpp"

#include "Menu_Music.hpp"
#include "FPS_Timer.hpp"

#include "SetupPvp.hpp"


class Menu
{
public:
	Menu();
	~Menu();

	bool loop();

	bool update(); //update menue
	void render(); //render menue to screen

	void reset();

	bool isActive();
	void setInactive();
	bool setActive();

	Btn_Type activeBtn();

	void free();

private:
	SetupPvp PvpMenu;

	Fps_Timer FpsTimer; // init & start fps timer
	Menu_Music Music;

	Escape_Overlay Esc_Overlay;
	//
	Click_EventHandler EventHandler;
	SDL_Event e;

	SDL_Rect rect;

	bool mIsActive;
	bool QuitGame = false;


	ButtonType mActiveButton;
	Btn_Type mActiveSubBtn;

	Menu_Button mButtons[4];
	Button mSubButton[5];

	bool initBtns();


};