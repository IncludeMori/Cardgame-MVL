//
// @Author: Moritz Volkenandt (2017-)
// main.cpp
#pragma once

// includes[...]
#include "SDL_init.hpp"
#include "GameLoop.hpp"


//global renderer -> render texture etc to screen
SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;

bool gQuitGame;

Mouse gMouse; // used to access current mouse data

// Window [ Size ]
const int SCREEN_WIDTH =1920;
const int SCREEN_HEIGHT = 1080;

//..............................
int main(int argc, char* args[])
{

	gQuitGame = false;
	// init SDL and create the window
	SDL_init SDL;
	SDL.SDLinit(SCREEN_WIDTH, SCREEN_HEIGHT, "WINDOW_NAME");
	

	GameClass myGame; //initialise game
		
	myGame.main_loop(); //start main loop

	 //quit sld
	SDL.SDLclose();

	return 0;
} // main
