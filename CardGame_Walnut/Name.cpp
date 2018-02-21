#include "Name.hpp"

#include "gScreenSize.hpp"

Name::Name()
{
	CurrentValue = "Player_Unkown";
	loadFromRenderedText(CurrentValue);
}


Name::~Name()
{
}

void Name::init(Who o,const std::string &name)
{
	//if (!name.empty())
	CurrentValue = name;
	loadFromRenderedText(CurrentValue);
	


	if (o == PLAYER)
	{
		setPos(700, SCREEN_HEIGHT - 150);
	}
	else
	{
		setPos(700, 240);
	}
}
void Name::setName(const std::string &name)
{

	CurrentValue = name;
	loadFromRenderedText(CurrentValue);
}
