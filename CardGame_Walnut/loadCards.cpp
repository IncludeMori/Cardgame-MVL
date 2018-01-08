#include "loadCards.hpp"

#include "GetFiles.hpp"

loadCards::loadCards()
{
}


loadCards::~loadCards()
{
}


void loadCards::load(std::vector<std::unique_ptr<Default_Card>> &cards)
{
	GetFiles files;
	
	std::vector<std::string> Filenames = files.getFiles("Cards_Lua/");

	for (int i = 0; i < files.getSize(); i++)
	{
		Filenames.at(i) = Filenames.at(i).substr(0, Filenames.at(i).find_last_of("."));
		cards.push_back(std::unique_ptr<Default_Card>(new Default_Card(Filenames.at(i),1)));
		cards.at(i)->loadTexture();
	}

}