#include "Field_HoverEffect.hpp"



Field_HoverEffect::Field_HoverEffect()
{
	mIsActive = false;
	loadFromFile("Data/card_hover.png");
}


Field_HoverEffect::~Field_HoverEffect()
{

}

void Field_HoverEffect::set(bool v)
{
	mIsActive = v;
}

void Field_HoverEffect::render()
{
	if (mIsActive)
		DefaultTexture::render();
}
