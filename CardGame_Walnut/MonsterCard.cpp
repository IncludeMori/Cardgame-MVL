

#include <iostream>
#include <memory>

#include "MonsterCard.hpp"
#include "sol\sol.hpp"
#include "gMouse.hpp"
#include "draw.hpp"
#include "Field.hpp"
#include "Card_Effects.hpp"
#include "BoostCard.hpp"
#include "Data.hpp"
#include "Renderer.hpp"
#include "Card_Stats_Type.hpp"
#include "Place.hpp"
#include "getEffectAsString.hpp"
#include "SDL_Deleter.hpp"

using namespace CARD_STATS_TYPE;

using namespace sdl2_Deleter;
using namespace sdl2_Renderer;

void deleter_t(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); std::cout << "sdl_texture destroyed" << std::endl; }

std::shared_ptr<SDL_Texture> loadTextureHelper(const std::string &path,int &width,int &height)
{
	std::cout << "Loading: " << path.c_str() << std::endl;

	std::shared_ptr<SDL_Texture> texture;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface)
	{
		throw std::runtime_error("Unable to load image at:" + path + "  Error:" + IMG_GetError());
	}
	else
	{
		//neutral colorkey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
	
		std::shared_ptr<SDL_Texture> newTexture(SDL_CreateTextureFromSurface(Renderer.get(), loadedSurface),deleter_t);
		if (!newTexture)
		{
			throw std::runtime_error("Failed to create texture from surface at " + path + "    Sdl_Error:" + SDL_GetError());
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		//move ptr to member
		texture = newTexture;
	}
	return texture;
}

MonsterCard::MonsterCard(std::string &path, int x)
{
	int w, h;
	std::string p = "Data/numbers.png";
	std::shared_ptr<SDL_Texture> ATexture = loadTextureHelper(p, w, h);

	//to do
	mStatsIcon.push_back(StatsSign(ATexture, w, h)); //cost
	mStatsIcon.push_back(StatsSign(ATexture, w, h)); //healtg
	mStatsIcon.push_back(StatsSign(ATexture, w, h)); //attack
	

	mCostIcon.setup(ATexture, w, h);
	mApIcon.setup(ATexture, w, h);
	mHealthIcon.setup(ATexture, w, h);

	getEffectAsString EffectToString;

	mActive = false;
	mAlive = true;
	mCanAttack = true;

	mBasicHealth = 0;
	mBasicAttack = 0;
	mBasicPlayCost = 0;


	sol::state lua;
	lua.script_file("Data/Cards_Lua/Cards_Lua/Data/card_effects.lua");
	std::cout << "Path:" << path << std::endl;
	lua.script_file("Data/Cards_Lua/Cards_Lua/" + path + ".lua");
	std::cout << "Lua script loaded: Data/Cards_Lua/Cards_Lua/" + path + ".lua" << std::endl;

	mName = path;

	int begin = path.find_last_of("/");
	int end = path.length();

	std::string name = path.substr(begin + 1, end);


	mBasicHealth = lua[name]["health"];
	mBasicAttack = lua[name]["atk"];
	mBasicPlayCost = lua[name]["cost"];
	mTexturePath = lua[name]["path"];

	mHealthIcon.changeDataTo(mBasicHealth);
	mCostIcon.changeDataTo(mBasicPlayCost);
	mApIcon.changeDataTo(mBasicAttack);

	std::vector<std::string> effects;
	mEffectType = static_cast<eEffect>(lua[name]["mEffect"]);
	effects.push_back(EffectToString.getAsString(StatIndex::Effect, lua[name]["mEffect"]));
	// switch effekt um jeweils andere sachen hiernach zu laden
	
	eType Type = static_cast<eType>(lua[name]["mType"]);
	effects.push_back(EffectToString.getAsString(StatIndex::Type, lua[name]["mType"]));
	eTarget Target = static_cast<eTarget>(lua[name]["mTarget"]);
	effects.push_back(EffectToString.getAsString(StatIndex::Target, lua[name]["mTarget"]));
	eTarget_spec Target_spec = eTarget_spec::ERROR;
	if (Target != eTarget::SELF)
	{
		Target_spec = static_cast<eTarget_spec>(lua[name]["mTarget_spec"]);
		effects.push_back(EffectToString.getAsString(StatIndex::Target_Spec, lua[name]["mTarget_spec"]));
	}
	eStat Stat = static_cast<eStat>(lua[name]["mStat"]);
	effects.push_back(EffectToString.getAsString(StatIndex::Stat, lua[name]["mStat"]));
	int amount = lua[name]["amount"];
	effects.push_back(lua[name]["amount"]);
	

	switch (mEffectType)
	{
	case(eEffect::BATTLECRY):
		switch (Type)
		{
		case(eType::BOOST):
			mEffect.reset(new BoostCard(Target,Target_spec,Stat,amount));
			break; //boost
		default:
			mEffectType = eEffect::ERROR;
			break;
		} // type
		break; //battlecry
	case(eEffect::DEATHWISH):
		break; //deathwish
	default:
		break;
	}

	begin = mTexturePath.find_last_of("/");
	end = mTexturePath.length();

	name = mTexturePath.substr(begin + 1, end);

	mHoverEffectTexture.loadFromFile("Data/Big/" + name);
	mHoverEffectTexture.setStats(mName, mBasicHealth, mBasicAttack, mBasicPlayCost, mRarity);
	mHoverEffectTexture.setEffect(effects);
	mFrame.load(mRarity,false);
	mIcon.load();
	mBackground.loadFromFile("Data/Cards/background.png");
	mHoverEffectTexture.disable();
	mHoverEffectTexture.setPos(30, SCREEN_HEIGHT / 2 - 275);
}
MonsterCard::MonsterCard(int Health, int Attack, int Type, std::string &path)
{
	mActive = false;
	mAlive = true;
	mCanAttack = true;

	mBasicHealth = Health;
	mBasicAttack = Attack;
	mBasicPlayCost = Type;
	mTexturePath = path;
	mHealthIcon.changeDataTo(mBasicHealth);
	mCostIcon.changeDataTo(mBasicPlayCost);
	mApIcon.changeDataTo(mBasicAttack);
}

MonsterCard::~MonsterCard()
{

}

void MonsterCard::play(const std::shared_ptr<Field> &Field)
{
	Field->addCard(shared_from_this());
}

void MonsterCard::update()
{
	mHoverEffectTexture.update();
	updateStats();
}

void MonsterCard::updateStats()
{
	mHealthIcon.changeDataTo(mBasicHealth);
	mCostIcon.changeDataTo(mBasicPlayCost);
	mApIcon.changeDataTo(mBasicAttack);
}

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
	using namespace CARD_DATA;

	static_cast<HoverCardEffect*>(param)->enable();
	
	return 0;
}

void MonsterCard::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	using namespace CARD_DATA;

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen


	mFrame.render();
	mIcon.render();

	renderIcons();

	if (mouseIsAbove())
	{
		if (mPlacePosition == Position::FIELD)
		{
			if (mTimerActive == false)
			{
				SDL_RemoveTimer(myTimer);
				myTimer = SDL_AddTimer(500, my_callbackfunc, &mHoverEffectTexture);//start new thread as timer
				mTimerActive = true;
			}
		}
		if (mHoverEffectTexture.isActive())
		{
			mHoverEffectTexture.render();
		}
	}
	else
		if (mHoverEffectTexture.isActive())
		{
			mHoverEffectTexture.disable();
			HoverEffectIsActive = false;
		}
}

void MonsterCard::render(bool &hoverIsActive, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	using namespace CARD_DATA;

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen

	mFrame.render();
	mIcon.render();

	renderIcons();

	if (mouseIsAbove())
	{
		if (mPlacePosition == Position::FIELD)
		{
			if (mTimerActive == false)
			{
				SDL_RemoveTimer(myTimer);
				myTimer = SDL_AddTimer(500, my_callbackfunc, &mHoverEffectTexture);//start new thread as timer
				
				mTimerActive = true;
			}
		}
		if (mHoverEffectTexture.isActive())
		{
			mHoverEffectTexture.render();
			hoverIsActive = true;
		}
		else
			hoverIsActive = false;
	}
	else
	{
		mHoverEffectTexture.disable();
		HoverEffectIsActive = false;
	}
}

void MonsterCard::renderCardback(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	mBackground.render();
}

void MonsterCard::renderIcons()
{
	SDL_SetRenderDrawColor(Renderer.get(), 100, 100, 100, 100);
	mHealthIcon.render();
	mCostIcon.render();
	mApIcon.render();
	SDL_SetRenderDrawColor(Renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
}

void MonsterCard::loadTexture() {
	//free();
	//mBackground.free();
	//mBackground.loadFromFile("Data/Cards/background.png");
	loadFromFile(mTexturePath);
}

bool MonsterCard::mouseIsAbove()
{
	using namespace CARD_DATA;

	int mouseX = gMouse.getX();
	int mouseY = gMouse.getY();
	if (mouseX > mPosX && mouseX < mPosX + mWidth && mouseY > mPosY && mouseY < mPosY + mHeight)
	{
		if (gMouse.isPressed())
		{
			if (mHoverEffectTexture.isActive())
			{
				mHoverEffectTexture.disable();
				HoverEffectIsActive = false;
				
				mTimerActive = false;
			}
		}
		else
			if (mPlacePosition == Position::HAND && !HoverEffectIsActive)
			{
				
				mHoverEffectTexture.enable();
				HoverEffectIsActive = true;
			}


		return true;
	}
	else {
		if (mPlacePosition == Position::FIELD)
		{
			if (mHoverEffectTexture.isActive())
			{
				mHoverEffectTexture.disable();
				HoverEffectIsActive = false;
				mTimerActive = false;
			}
		}
		return false; }
}

void MonsterCard::moveSigns(int x, int y)
{
	mHealthIcon.move(x,y);
	mCostIcon.move(x, y);
	mApIcon.move(x, y);
}

void MonsterCard::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
	mBackground.setPos(x, y);
	
	mFrame.setPos(x, y);
	mIcon.setPos(x, y);
	mCostIcon.setPos(x, y);
	mApIcon.setPos(x, y + mHeight-mApIcon.getHeight());
	mHealthIcon.setPos(x + mWidth-mHealthIcon.getWidth(), y + mHeight-mHealthIcon.getHeight());

	/*
	switch (mPlacePosition)
	{
	case(Position::HAND):
		mHoverEffectTexture.setPos(x - 50, y - 400);
		break;
	case(Position::FIELD):
		mHoverEffectTexture.setPos(x + 200, y - 75);
		break;

		
	}*/
	mHoverEffectTexture.update();
	
}
bool MonsterCard::activateEffect()
{
	bool x = mEffect->activate(this);
	
	mHealthIcon.changeDataTo(mBasicHealth);
	mCostIcon.changeDataTo(mBasicPlayCost);
	mApIcon.changeDataTo(mBasicAttack);
	return x;

}

void MonsterCard::increase(eStat stat, int amount)
{
	switch (stat)
	{
	case(eStat::ATTACK):
		mBasicAttack += amount;
		break;
	case(eStat::HEALTH):
		mBasicHealth += amount;
		break;
	case(eStat::COST):
		mBasicPlayCost += amount;
		break;
	}
	updateStats();
}
void MonsterCard::increaseAtk(int amount)
{
	mBasicAttack += amount;
	mApIcon.changeDataTo(mBasicAttack);
}
void MonsterCard::increaseHealth(int amount)
{
	mBasicHealth += amount;
}


bool MonsterCard::canAttack()
{
	return mCanAttack;
}


void MonsterCard::removeHealth(int amount)
{
	mBasicHealth -= amount;
	mHealthIcon.changeDataTo(mBasicHealth);
	if (mBasicHealth <= 0) { mAlive = false; }
	std::cout << "Health left:" << mBasicHealth << std::endl;
	if (mAlive == false) { std::cout << "dead" << std::endl; }
}
bool MonsterCard::isAlive()
{
	return mAlive;
}

eEffect MonsterCard::getEffect()
{
	return mEffectType;
}
std::string MonsterCard::getName()
{
	return mName;
}
int MonsterCard::getHealth()
{
	return mBasicHealth;
}
int MonsterCard::getAttack()
{
	return mBasicAttack;
}

void MonsterCard::setHover(bool &b)
{
	if (mouseIsAbove())
	{
		if (mPlacePosition == Position::FIELD)
		{
			if (mTimerActive == false)
			{
				SDL_RemoveTimer(myTimer);
				myTimer = SDL_AddTimer(500, my_callbackfunc, &mHoverEffectTexture);//start new thread as timer

				mTimerActive = true;
			}
		}
		if (mHoverEffectTexture.isActive())
		{
			mHoverEffectTexture.render();
			b = true;
		}
		else
			b = false;
	}
	else
	{
		mHoverEffectTexture.disable();
		b = false;
	}
}