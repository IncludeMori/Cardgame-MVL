#include "Collection_Menu.hpp"
#include "fdeleter.hpp"
#include "Sub_Btn_Enum.hpp"
#include "Create_Deck.hpp"

#include "Menu.hpp"
#include "Game.hpp"

using std::unique_ptr;

class GameClass
{
public:
	GameClass();

	bool main_loop();

private:
	//const Uint8* key = SDL_GetKeyboardState(NULL);

	unique_ptr<Menu> mMenu = nullptr;
	unique_ptr<Game> mGame = nullptr;
	unique_ptr<Create_Deck, fdeleter> mCreateDeck = nullptr;

	Btn_Type mCurrentlyActive;

	bool mCollectionInit;
};