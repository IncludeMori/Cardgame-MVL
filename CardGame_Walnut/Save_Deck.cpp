#include "Save_Deck.hpp"

#include <fstream>

bool Save_Deck::save(std::string &deck,int index)
{
	if (index >= 0 && index <= 9)
	{
		std::ofstream file("Save/player_deck.txt");

		file << deck;

		file.close();

		return true;

	}
	else 
		return false;

}