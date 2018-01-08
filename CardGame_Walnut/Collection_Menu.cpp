#include "Collection_Menu.hpp"

Collection::Collection()
{
	isActive = true;
	mCreateDeckBtn.loadFromFile("Data/deck_btn.png");
	mSeeDeckBtn.loadFromFile("Data/collection_btn.png");
}

bool Collection::update()
{
	if (isActive)
	{
		SDL_PollEvent(&e);
		EventHandler.handleEvent(e);

		if (mCreateDeckBtn.IsPressed() || mSeeDeckBtn.IsPressed())
		{
			isActive = false;
			SDL_Delay(500);
		}

	}
	else //menue not active
	{
		if (mCreate.createDeck()) //wait for user to finish 
		{
			//afterwards set menu active-> go back
			isActive = true;
			return false;
		}
	}

	return true;
}
void Collection::render()
{
	if (isActive)
	{
		mCreateDeckBtn.render();
		mSeeDeckBtn.render();
	}
	else
	{
		mCreate.createDeck();
	}
}

void Collection::free()
{
	mCreate.free();

	mCreateDeckBtn.free();
	mSeeDeckBtn.free();
}
