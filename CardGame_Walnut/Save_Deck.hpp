//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: save the deck as string
//
#pragma once

#include <string>

class Save_Deck
{
public:
	bool save(std::string &deck, int index); // index -> deck slot
};