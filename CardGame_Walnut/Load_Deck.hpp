//
// @Author: Moritz Volkenandt (2017-)
//
// Purpose: Load string from txt file
//
#pragma once

#include <string>
#include <vector>

class Load_Deck
{
public:
	std::vector<std::string> load();

	std::vector<std::string> loadMonster();
	std::vector<std::string> loadZauber();

	std::vector<std::string> loadDeck();
};