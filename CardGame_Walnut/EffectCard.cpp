#include "EffectCard.hpp"

#include "sol\sol.hpp"

#include "eCard_Effects.hpp"
#include "gMouse.hpp"

#include "eCard_Effects.hpp"
#include "HealOrDmg.hpp"

#include <iostream>

#include "Place.hpp"

#include "Player_Field.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

EffectCard::EffectCard()
{
}

EffectCard::EffectCard(std::string &path)
{
	mBasicPlayCost = 0;


	sol::state lua;
	lua.script_file("Data/Cards_Lua/Cards_Lua/Data/eCard_effects.lua");
	lua.script_file("Data/Cards_Lua/Cards_Lua/MagicCards/" + path + ".lua");

	mName = path;

	int begin = path.find_last_of("/");
	int end = path.length();

	std::string name = path.substr(begin + 1, end);
	mBasicPlayCost = lua[name]["cost"];
	mTexturePath = lua[name]["path"];

	loadFromFile(mTexturePath);

	mCostIcon.changeDataTo(mBasicPlayCost);

	Zauber mZauber = static_cast<Zauber>(lua[name]["mEffect"]);
	

	int amount = lua[name]["amount"];
	switch (mZauber)
	{
	case(Zauber::Damage):
	
		std::cout << "Damage.";
		mEffect.reset(new HealOrDmg(amount*-1));

	break;
	case(Zauber::Boost):
		mEffect.reset(new HealOrDmg(amount));

	break;
	}

	//->mEffectType = static_cast<eEffect>(lua[name]["mEffect"]);
	// switch effekt um jeweils andere sachen hiernach zu laden

	

	begin = mTexturePath.find_last_of("/");
	end = mTexturePath.length();

	name = mTexturePath.substr(begin + 1, end);

	std::cout << "NAME:" << name << std::endl;
	std::cout << mName << std::endl;
	mHoverEffectTexture.loadFromFile("Data/Big/" + name);
	mHoverEffectTexture.setStats(mName, mBasicPlayCost, mRarity);
	mHoverEffectTexture.disable();
	mHoverEffectTexture.setPos(30, SCREEN_HEIGHT / 2 - 275);
	


	update();
}


void EffectCard::play(const std::shared_ptr<Field> &Field)
{
	Field->addEffectCard(shared_from_this());
}



void EffectCard::renderIcons()
{
	mCostIcon.render();
}

void EffectCard::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen

	renderIcons();

	if (mouseIsAbove())
	{
		if (mHoverEffectTexture.isActive())
		{
			mHoverEffectTexture.render();
		}
	}
}

void EffectCard::render(bool &hoverIsActive, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen

	renderIcons();

	if (mouseIsAbove())
	{
		if (mHoverEffectTexture.isActive())
		{
			mHoverEffectTexture.render();
			hoverIsActive = true;
		}
		else
			hoverIsActive = false;
	}
}

void EffectCard::renderCardback(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen
}

bool EffectCard::activateEffect()
{
	return mEffect->activate();
}
bool EffectCard::mouseIsAbove()
{
		if (gMouse.isPressed())
		{
			if (mHoverEffectTexture.isActive())
				mHoverEffectTexture.disable();
		}
		else
			mHoverEffectTexture.enable();


		int mouseX = gMouse.getX();
		int mouseY = gMouse.getY();
		if (mouseX > mPosX && mouseX < mPosX + mWidth && mouseY > mPosY && mouseY < mPosY + mHeight)
		{
			return true;
		}
			return false;
}
void EffectCard::moveSigns(int x, int y)
{
	mCostIcon.move(x, y);
}

void EffectCard::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mCostIcon.setPos(x, y);
	
	//if (mPlacePosition == Position::HAND)
	//	mHoverEffectTexture.setPos(x - 50, y - 400);

}