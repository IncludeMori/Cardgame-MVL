#include "Effect_Description.hpp"



Effect_Description::Effect_Description()
{
	mBackground.loadFromFile("Data/BigCard_Interface/background_descr.png");
	//mEffectDescr.resize(4);
	//int size = 24;
	//mEffectDescr.at(0).loadFromRenderedText(size,"Battlecry");
	//mEffectDescr.at(1).loadFromRenderedText(size,"Deal Dmg");
	//mEffectDescr.at(2).loadFromRenderedText(size,"Amount: 5");
	//mEffectDescr.at(3).loadFromRenderedText(size,"Test");

	//for (int i=0;i<mEffectDescr.size();i++)
		//
}


Effect_Description::~Effect_Description()
{
}

void Effect_Description::render()
{
	mBackground.render();

	for (unsigned int i = 0; i < mEffectDescr.size(); i++)
		mEffectDescr.at(i).render();
}
void Effect_Description::setPos(int x, int y)
{
	mBackground.setPos(x, y);

	for (unsigned int i=0;i<mEffectDescr.size();i++)
	mEffectDescr.at(i).setPos(x+5, y+(i*30));

	//....
}

void Effect_Description::setEffect(std::vector<std::string> &effects)
{
	mEffectDescr.resize(effects.size());
	int size = 24;

	for (unsigned int i = 0; i < mEffectDescr.size(); i++)
		mEffectDescr.at(i).loadFromRenderedText(size, effects.at(i));

}

void Effect_Description::free()
{
	mBackground.free();
	
	for (unsigned int i = 0; i < mEffectDescr.size(); i++)
		mEffectDescr.at(i).free();
}