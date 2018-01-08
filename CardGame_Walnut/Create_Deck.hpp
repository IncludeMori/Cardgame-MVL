#pragma once

#include <string>
#include <vector>

#include "Load_Deck.hpp"
#include "Collection_Card.hpp"

#include "Button.hpp"
#include "CL_EventHandler.hpp"
#include <memory>
#include "HeroHealth.hpp"
#include "gScreenSize.hpp"

//
// show old deck + create deck button
// if -> create deck
// ----> "The old deck will be deleted. Are you sure you want to create a new one?"
// ------> Save: save new deck, delete old one
// if -> back
// ----> go back to main menue

class Create_Deck
{
public:
	Create_Deck();
	~Create_Deck();

	bool loop();

	bool update();
	void render();

	bool createDeck();

	void free();

private:
	void updatePos();
	void loadAllCards();
	bool fsaveDeck();

	int mPage;
	int Max_Page;

	bool CardAdded;
	bool CardRemoved;

	HeroHealth DeckSizeSign;
	HeroHealth PageSign;

	SDL_Event e;
	CL_EventHandler EventHandler;

	//Pos
	std::vector<int> mPosX;
	std::vector<int> mPosY;

	std::vector<int> mSmallPosX;
	std::vector<int> mSmallPosY;

	int DeckSize;
	int Max_DeckSize;

	bool Deck_Saved;
	bool not_done;
	bool QuitGame = false;

	std::vector<std::unique_ptr<Default_Card>> mCards;
	std::vector<std::unique_ptr<Collection_Card>> mCurrentDeckCards;
	int hover_card;
	std::vector<std::unique_ptr<Collection_Card>>::iterator mIt;
	std::vector<std::string> mAllCards;

	std::string mPath; // Save Deck to path
	std::string mDeck; // 

	Button goBackBtn{ 0,0 };
	Button newDeckBtn{ 200,200 };
	Button saveDeck{ SCREEN_WIDTH - SCREEN_WIDTH / 4,SCREEN_HEIGHT - SCREEN_HEIGHT / 10 };
	DefaultTexture Deck_Size{ SCREEN_WIDTH / 2 + SCREEN_WIDTH / 15 + 100, SCREEN_HEIGHT / 50 };

	DefaultTexture tDeck_Saved{ SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 200 };
	Button OkBtn{ SCREEN_WIDTH / 2 - 100,SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 10 - 175 };

	Button leftT{ SCREEN_WIDTH / 18,SCREEN_HEIGHT / 2 };
	Button right{ SCREEN_WIDTH / 2 + SCREEN_WIDTH / 10,SCREEN_HEIGHT / 2 };
};
