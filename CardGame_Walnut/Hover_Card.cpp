#include "Hover_Card.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

Hover_Card::Hover_Card()
{
	mIcons.loadFromFile("Data/BigCard_Interface/Icons.png");
	mFrame.load(Rarity::Bronze, true);
}

Hover_Card::Hover_Card(std::string &name, int health, int atk, int cost,Rarity rarity)
{
	mIsActive = false;
	mHealth = health;
	mAttack = atk;
	mCost = cost;
	mRarity = rarity;

	mIcons.loadFromFile("Data/BigCard_Interface/Icons.png");
	mFrame.load(rarity,true);

	mNameplate.setName(name);
}

void Hover_Card::update()
{
	mIcons.setPos(mPosX, mPosY);
	mFrame.setPos(mPosX, mPosY);
	mNameplate.setPos(mPosX, mPosY);
	mEffectDescr.setPos(mPosX, mPosY+mHeight+5);

	mSCost.setPos(mPosX + 5, mPosY + 5);
	mSHealth.setPos(mPosX + 200, mPosY + 320);
	mSAttack.setPos(mPosX + 5, mPosY + 320);


}

void Hover_Card::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mWidth, mHeight };


	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen
	mFrame.render();
	mIcons.render();
	mNameplate.render();
	mEffectDescr.render();

	mSAttack.render();
	mSCost.render();
	mSHealth.render();
}


void Hover_Card::enable()
{
	mIsActive = true;
}
void Hover_Card::disable()
{
	mIsActive = false;
}

bool Hover_Card::isActive()
{
	return mIsActive;
}

void Hover_Card::setStats(std::string &name, int health, int atk, int cost, Rarity rarity)
{
	mIsActive = false;
	mHealth = health;
	mAttack = atk;
	mCost = cost;
	mRarity = rarity;
	mFrame.load(rarity, true);
	mNameplate.setName(name);

	mSCost.changeDataTo(mCost);
	mSHealth.changeDataTo(mHealth);
	mSAttack.changeDataTo(mAttack);
}

void Hover_Card::setEffect(std::vector<std::string> &effects)
{
	mEffectDescr.setEffect(effects);
}