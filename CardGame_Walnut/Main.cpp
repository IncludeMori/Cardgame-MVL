//
// @Author: Moritz Volkenandt (2017-)
// main.cpp
#pragma once

// includes[...]
#include "SDL_init.hpp"
#include "GameLoop.hpp"

bool gQuitGame;

Mouse gMouse; // used to access current mouse data

// Window [ Size ]
const int SCREEN_WIDTH =1920;
const int SCREEN_HEIGHT = 1080;

void game()
{
	gQuitGame = false;
	// init SDL and create the window
	sdl2_Init::startSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Walnut");

	GameClass myGame; //initialise game
	myGame.main_loop(); 			
	sdl2_Init::closeSDL();
}

int main(int argc, char* args[])
{
	game();
	return 0;
} 
