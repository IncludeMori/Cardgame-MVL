#include "Hover_Card.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

HoverCardEffect::HoverCardEffect()
{
	mIcon.loadFromFile("Data/BigCard_Interface/Icons.png");
	mFrame.load(Rarity::Bronze, true);
}

HoverCardEffect::HoverCardEffect(std::string &name, int health, int atk, int cost,Rarity rarity)
{
	mIsActive = false;
	mHealth = health;
	mAttack = atk;
	mCost = cost;
	mRarity = rarity;

	mIcon.loadFromFile("Data/BigCard_Interface/Icons.png");
	mFrame.load(rarity,true);

	mNameplate.setName(name);
}

HoverCardEffect::HoverCardEffect(std::string& name, int cost, Rarity rarity) {

	mIsActive = false;
	mCost = cost;
	mRarity = rarity;

	mIcon.loadFromFile("Data/BigCard_Interface/Icons.png");
	mFrame.load(rarity, true);

	mNameplate.setName(name);
}

void HoverCardEffect::update()
{
	mIcon.setPos(mPosX, mPosY);
	mFrame.setPos(mPosX, mPosY);
	mNameplate.setPos(mPosX, mPosY);
	mEffectDescr.setPos(mPosX, mPosY+mHeight+5);

	mSCost.setPos(mPosX + 5, mPosY + 5);
	mSHealth.setPos(mPosX + 200, mPosY + 320);
	mSAttack.setPos(mPosX + 5, mPosY + 320);


}

void HoverCardEffect::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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
	mIcon.render();
	mNameplate.render();
	mEffectDescr.render();

	mSAttack.render();
	mSCost.render();
	mSHealth.render();
}


void HoverCardEffect::enable()
{
	mIsActive = true;
}
void HoverCardEffect::disable()
{
	mIsActive = false;
}

bool HoverCardEffect::isActive()
{
	return mIsActive;
}

void HoverCardEffect::setStats(std::string& name, int cost, Rarity rarity)
{
	mIsActive = false;
	mCost = cost;
	mRarity = rarity;
	mFrame.load(rarity, true);
	mNameplate.setName(name);

	mSCost.changeDataTo(mCost);
}
void HoverCardEffect::setStats(std::string &name, int health, int atk, int cost, Rarity rarity)
{
	setStats(name, cost, rarity);
	
	mHealth = health;
	mAttack = atk;

	mSHealth.changeDataTo(mHealth);
	mSAttack.changeDataTo(mAttack);
}

void HoverCardEffect::setEffect(std::vector<std::string> &effects)
{
	mEffectDescr.setEffect(effects);
}