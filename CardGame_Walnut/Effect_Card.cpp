#include "Effect_Card.hpp"

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

Effect_Card::Effect_Card()
{
}

Effect_Card::Effect_Card(std::string &path)
{
	mBasicCost = 0;


	sol::state lua;
	lua.script_file("Data/Cards_Lua/Cards_Lua/Data/eCard_effects.lua");
	lua.script_file("Data/Cards_Lua/Cards_Lua/MagicCards/" + path + ".lua");

	mName = path;

	int begin = path.find_last_of("/");
	int end = path.length();

	std::string name = path.substr(begin + 1, end);
	mBasicCost = lua[name]["cost"];
	mPath = lua[name]["path"];

	loadFromFile(mPath);

	mCostSign.changeDataTo(mBasicCost);

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

	

	begin = mPath.find_last_of("/");
	end = mPath.length();

	name = mPath.substr(begin + 1, end);

	HoverEffect.loadFromFile("Data/Big/" + name);

	HoverEffect.disable();
	
}


void Effect_Card::play(const std::shared_ptr<Field> &Field)
{
	Field->addEffectCard(shared_from_this());
}



void Effect_Card::renderSigns()
{
	mCostSign.render();
}

void Effect_Card::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen

	renderSigns();

	if (MouseIsAbove())
	{
		if (HoverEffect.isActive())
		{
			HoverEffect.render();
		}
	}
}

void Effect_Card::render(bool &hoverIsActive, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen

	renderSigns();

	if (MouseIsAbove())
	{
		if (HoverEffect.isActive())
		{
			HoverEffect.render();
			hoverIsActive = true;
		}
		else
			hoverIsActive = false;
	}
}

void Effect_Card::renderBackside(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

bool Effect_Card::activateEffect()
{
	return mEffect->activate();
}
bool Effect_Card::MouseIsAbove()
{
		if (gMouse.isPressed())
		{
			if (HoverEffect.isActive())
				HoverEffect.disable();
		}
		else
			HoverEffect.enable();


		int mouseX = gMouse.getX();
		int mouseY = gMouse.getY();
		if (mouseX > mPosX && mouseX < mPosX + mWidth && mouseY > mPosY && mouseY < mPosY + mHeight)
		{
			return true;
		}
			return false;
}
void Effect_Card::moveSigns(int x, int y)
{
	mCostSign.move(x, y);
}

void Effect_Card::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mCostSign.setPos(x, y);
	
	if (mPos == Position::HAND)
		HoverEffect.setPos(x - 50, y - 400);

}