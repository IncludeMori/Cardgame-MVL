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

class Game
{
public:
	Game();
	~Game();

	bool loop();

	bool update();
	void render();

	void Init();

	void free();
private:
	bool QuitGame = false;
	Escape_Overlay Esc_Overlay;
	GameEndScreen End_Screen;

	DefaultTexture mBackground;
	bool keyUp;

	Click_EventHandler EventHandler;
	SDL_Event e;

	std::shared_ptr<CurrentTurn> mTurn = nullptr;

	std::shared_ptr<Player> mPlayer = nullptr;
	std::shared_ptr<Opponent> mOpponent = nullptr;


};