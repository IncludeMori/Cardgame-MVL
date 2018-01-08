#include "Load_Deck.hpp"

#include <fstream>
#include <iostream>

std::vector<std::string> Load_Deck::load()
{
	std::ifstream file("Save/player_deck.txt");
	std::string deck;
	std::vector<std::string> cards;

	if (file.is_open())
	{
		if (std::getline(file, deck))
		{
			file.close();
		}
	}

	std::string current;
	int index = 0;
	int start = 0, end = -1;
	int size = 0;
	while (start < deck.size()-1)
	{
		end = deck.find("0", start + 1);
		size = end - (start + 1);
		std::cout << "start:" << start << ",end:" << end << std::endl;

		current = deck.substr(start, size+1);
		cards.push_back(current);
		std::cout << "Current:" << current << std::endl;

		start = end + 1;
	}

	return cards;
}

std::vector<std::string> Load_Deck::loadMonster()
{
	std::ifstream file("Save/player_deck.txt");
	std::string deck;
	std::vector<std::string> cards;

	if (file.is_open())
	{
		if (std::getline(file, deck))
		{
			file.close();
		}
	}

	std::string current;
	int index = 0;
	int start = 0, end = -1;
	int size = 0;
	while (start < deck.size() - 1)
	{
		end = deck.find("0", start + 1);
		size = end - (start + 1);
		

		current = deck.substr(start, size + 1);
		cards.push_back(current);
		

		start = end + 1;
	}

	return cards;
}
std::vector<std::string> Load_Deck::loadZauber()
{
	std::ifstream file("Save/player_deck.txt");
	std::string deck;
	std::vector<std::string> cards;

	if (file.is_open())
	{
		if (std::getline(file, deck))
			if (std::getline(file,deck))
			    file.close();
	}
	std::cout << "DECK:" << deck << std::endl;
	std::string current;
	int index = 0;
	int start = 0, end = -1;
	int size = 0;
	
	while (start < deck.size() - 1)
	{
		end = deck.find("0", start + 1);
		size = end - (start + 1);

		current = deck.substr(start, size + 1);
		cards.push_back(current);
	

		start = end + 1;
	}
	
	return cards;
}

std::vector<std::string> Load_Deck::loadDeck()
{
	std::ifstream file("Save/player_deck_new.txt");
	std::vector<std::string> deck;
	deck.resize(30);
	
	if (file.is_open())
	for (int i = 0; i < 30; i++)
	{
		std::getline(file, deck.at(i));
		std::cout << "CARD AT:" << i << ":" << deck.at(i).substr(1,deck.at(i).size()) << std::endl;
	}

	return deck;
}