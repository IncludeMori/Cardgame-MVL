#include "Frame.hpp"



Frame::Frame()
{
}


Frame::~Frame()
{
}


void Frame::load(Rarity rarity,bool big)
{
	std::string path;
	if (!big)
		path = "Data/Card_Interface/";
	else
		path = "Data/BigCard_Interface/";

	switch (rarity)
	{
	case(Rarity::Bronze):
		loadFromFile(path+"frame_bronze.png");
		break;
	case(Rarity::Silver):
		loadFromFile(path+"frame_silver.png");
		break;
	case(Rarity::Gold):
		loadFromFile(path+"frame_gold.png");
		break;
	}

}