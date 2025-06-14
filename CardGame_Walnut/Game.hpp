//
// @Author: Moritz Volkenandt (2017-)
// 
// gameplay
//
#pragma once

#include "gMouse.hpp"
#include "Player.hpp"
#include "CurrentTurn.hpp"
#include "Menu.hpp"
#include "Click_EventHandler.hpp"

#include "Escape_Overlay.hpp"
#include "GameEndScreen.hpp"

#include "FPS_Timer.hpp"

class Game
{
public:
	Game();
	~Game();

	bool loop();

	bool update();
	void render();

	void init();

	void free();
private:
	bool QuitGame;
	Escape_Overlay Esc_Overlay;
	GameEndScreen End_Screen;

	DefaultTexture mBackground;
	bool keyUp;

	Click_EventHandler EventHandler;
	SDL_Event mCurrentEvent;

	std::shared_ptr<CurrentTurn> mTurn = nullptr;

	std::shared_ptr<Player> mPlayer = nullptr;
	std::shared_ptr<Opponent> mOpponent = nullptr;

	Fps_Timer FpsTimer; // init & start fps timer


};