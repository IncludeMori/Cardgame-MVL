#pragma once

#include "Button.hpp"

#include "gScreenSize.hpp"
#include "Create_Deck.hpp"
#include "Click_EventHandler.hpp"

class Collection
{
public:
	Collection();

	bool update();
	void render();

	void free();

private:
	Button mSeeDeckBtn{ SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 100 };
	Button mCreateDeckBtn{ SCREEN_WIDTH / 2 - 200 , SCREEN_HEIGHT / 2 - 100 };

	Click_EventHandler EventHandler;
	SDL_Event e;

	Create_Deck mCreate;

	bool isActive;


};