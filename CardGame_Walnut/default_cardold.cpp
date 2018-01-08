#include "Default_Card.hpp"

#include <iostream>
Default_Card::Default_Card()
{
	mEmpty = true;
	mActive = false;
}
Default_Card::Default_Card(int Health, int Attack,int Type,std::string path)
{
	mEmpty = false;
	mActive = false;

	mHealth = Health;
	mAttack = Attack;
	mType = Type;
	mPath = path;
}
Default_Card::~Default_Card()
{
	free();
}

void Default_Card::update()
{

}

void Default_Card::render()
{
	if (!mCard.isEmpty())
	{
		mCard.render();
	}
	else { std::cout << "Card:" << mName << "..is empty" << std::endl; }
}

void Default_Card::loadTexture() {
	mCard.loadFromFile(mPath);
}

bool Default_Card::isEmpty()
{
	return mCard.isEmpty();
}

void Default_Card::setActive()
{
	mActive = true;
}
void Default_Card::setInactive()
{
	mActive = false;
}
bool Default_Card::isActive()
{
	return mActive;
}

void Default_Card::move(int x, int y)
{
	mCard.move(x, y);
}

std::string Default_Card::getName()
{
	return mName;
}
int Default_Card::getHealth()
{
	return mHealth;
}
int Default_Card::getAttack()
{
	return mAttack;
}

SDL_Rect Default_Card::getData()
{
	return mData;
}


void Default_Card::free()
{

}