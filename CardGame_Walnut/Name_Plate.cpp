#include "Name_Plate.hpp"



Name_Plate::Name_Plate()
{
	mName = "CARD_NAME";
	mTTFName.loadFromRenderedText(mName);
	mBackground.loadFromFile("Data/BigCard_Interface/name_plate.png");

}

Name_Plate::Name_Plate(std::string &name)
{
	mName = name;
	mTTFName.loadFromRenderedText(mName);
	mBackground.loadFromFile("Data/BigCard_Interface/name_plate.png");
}
Name_Plate::~Name_Plate()
{
}

void Name_Plate::render()
{
	mBackground.render();
	mTTFName.render();
}

void Name_Plate::setPos(int x, int y)
{

	y = y - 55;
	mBackground.setPos(x, y);
	mTTFName.setPos(x + (260-mTTFName.getWidth())/2, y + mBackground.getHeight() / 2-20);
}
void Name_Plate::setName(std::string &name)
{
	mName = name;
	
	mTTFName.loadFromRenderedText(mName);
}