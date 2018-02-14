#include "gRenderer.hpp"
#include "Default_Card.hpp"
#include <iostream>
#include "sol\sol.hpp"
#include "gMouse.hpp"
#include "draw.hpp"

#include "Field.hpp"
#include "Card_Effects.hpp"
#include <memory>
#include "BoostCard.hpp"
//#include "BoostCard.hpp"


#include "Place.hpp"

#include "getEffectAsString.hpp"

Default_Card::Default_Card()
{
	mActive = false;
	mAlive = true;
}

Default_Card::Default_Card(std::string &path)
{
	
	


	mActive = false;
	mAlive = true;
	mCanAttack = true;

	mBasicHealth = 0;
	mBasicAttack = 0;
	mBasicCost = 0;
	
	
	sol::state lua;
	lua.script_file(path+".lua");

	int begin = path.find_last_of("/");
	int end = path.length();
	
	std::string name = path.substr(begin + 1, end);
	mName = name;

	mBasicHealth = lua[name]["health"];
	mBasicAttack = lua[name]["atk"];
	mBasicCost = lua[name]["cost"];
	mPath = lua[name]["path"];

	mHealthSign.changeData(mBasicHealth);
	mCostSign.changeData(mBasicCost);
	mAPSign.changeData(mBasicAttack);

	HoverEffect.loadFromFile("Data/"+name+".png");


}
Default_Card::Default_Card(std::string &path, int x)
{
	
	getEffectAsString EffectToString;

	mActive = false;
	mAlive = true;
	mCanAttack = true;

	mBasicHealth = 0;
	mBasicAttack = 0;
	mBasicCost = 0;


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
	mBasicCost = lua[name]["cost"];
	mPath = lua[name]["path"];

	mHealthSign.changeData(mBasicHealth);
	mCostSign.changeData(mBasicCost);
	mAPSign.changeData(mBasicAttack);

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
	// switch with enum instead??
   // if (effect == 1)
	//{
	//	mEffect.reset(new BoostCard(amount, Stat::ATTACK));
	//}

	begin = mPath.find_last_of("/");
	end = mPath.length();

	name = mPath.substr(begin + 1, end);

	HoverEffect.loadFromFile("Data/Big/" + name);
	HoverEffect.setStats(mName, mBasicHealth, mBasicAttack, mBasicCost, mRarity);
	HoverEffect.setEffect(effects);
	mFrame.load(mRarity,false);
	mIcons.load();
	mBackground.free();
	mBackground.loadFromFile("Data/Cards/background.png");
	HoverEffect.disable();
}
Default_Card::Default_Card(int Health, int Attack, int Type, std::string &path)
{

	
	mActive = false;
	mAlive = true;
	mCanAttack = true;

	mBasicHealth = Health;
	mBasicAttack = Attack;
	mBasicCost = Type;
	mPath = path;
	mHealthSign.changeData(mBasicHealth);
	mCostSign.changeData(mBasicCost);
	mAPSign.changeData(mBasicAttack);
}

Default_Card::~Default_Card()
{
	free();
}

void Default_Card::play(const std::shared_ptr<Field> &Field)
{
	Field->addCard(shared_from_this());
}

void Default_Card::update()
{


}
void Default_Card::updateStats()
{
	mHealthSign.changeData(mBasicHealth);
	mCostSign.changeData(mBasicCost);
	mAPSign.changeData(mBasicAttack);
}

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
	std::cout << "function called" << std::endl;
	static_cast<Hover_Card*>(param)->enable();
	return 0;
}

void Default_Card::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip); // renders texture to screen


	mFrame.render();
	mIcons.render();

	renderSigns();

	if (MouseIsAbove())
	{
		if (mPos == Position::FIELD)
		{
			if (mTimerActive == false)
			{
				SDL_RemoveTimer(myTimer);
				std::cout << "start timer thread" << std::endl;
				myTimer = SDL_AddTimer(500, my_callbackfunc, &HoverEffect);//start new thread as timer
				mTimerActive = true;
			}
		}
		if (HoverEffect.isActive())
		{
			HoverEffect.render();
		}
	}
}
void Default_Card::render(bool &hoverIsActive, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip); // renders texture to screen

	mFrame.render();
	mIcons.render();

	renderSigns();

	if (MouseIsAbove())
	{
		if (mPos == Position::FIELD)
		{
			if (mTimerActive == false)
			{
				SDL_RemoveTimer(myTimer);
				std::cout << "start timer thread" << std::endl;
				myTimer = SDL_AddTimer(500, my_callbackfunc, &HoverEffect);//start new thread as timer
				mTimerActive = true;
			}
		}
		if (HoverEffect.isActive())
		{
			HoverEffect.render();
			hoverIsActive = true;
		}
		else
			hoverIsActive = false;
	}
	else
		HoverEffect.disable();
}

void Default_Card::renderBackside(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	/*/
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip); // renders texture to screen*/

	//mBackground.setPos(10, 10);
	mBackground.render();
}

void Default_Card::renderSigns()
{
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);
	mHealthSign.render();
	mCostSign.render();
	mAPSign.render();
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Default_Card::loadTexture() {
	//free();
	//mBackground.free();
	//mBackground.loadFromFile("Data/Cards/background.png");
	loadFromFile(mPath);
}

bool Default_Card::MouseIsAbove()
{
	if (gMouse.isPressed())
	{
		if (HoverEffect.isActive())
		{
			HoverEffect.disable();
			mTimerActive = false;
		}
	}
	else
		if (mPos == Position::HAND)
			HoverEffect.enable();


	int mouseX = gMouse.getX();
	int mouseY = gMouse.getY();
	if (mouseX > mPosX && mouseX < mPosX + mWidth && mouseY > mPosY && mouseY < mPosY + mHeight)
	{
		return true;
	}
	else {
		if (mPos == Position::FIELD)
		{
			if (HoverEffect.isActive())
			{
				HoverEffect.disable();
				mTimerActive = false;
			}
		}
		return false; }
}

void Default_Card::moveSigns(int x, int y)
{
	mHealthSign.move(x,y);
	mCostSign.move(x, y);
	mAPSign.move(x, y);
}

void Default_Card::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
	mBackground.setPos(x, y);
	
	mFrame.setPos(x, y);
	mIcons.setPos(x, y);
	mCostSign.setPos(x, y);
	mAPSign.setPos(x, y + mHeight-mAPSign.getHeight());
	mHealthSign.setPos(x + mWidth-mHealthSign.getWidth(), y + mHeight-mHealthSign.getHeight());

	switch (mPos)
	{
	case(Position::HAND):
		HoverEffect.setPos(x - 50, y - 400);
		break;
	case(Position::FIELD):
		HoverEffect.setPos(x + 200, y - 75);
		break;

		
	}
	HoverEffect.update();
	
}
bool Default_Card::activateEffect()
{
	bool x = mEffect->activate(this);
	
	mHealthSign.changeData(mBasicHealth);
	mCostSign.changeData(mBasicCost);
	mAPSign.changeData(mBasicAttack);
	return x;

}

void Default_Card::increase(eStat stat, int amount)
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
		mBasicCost += amount;
		break;
	}
	updateStats();
}
void Default_Card::increaseAtk(int amount)
{
	mBasicAttack += amount;
	mAPSign.changeData(mBasicAttack);
}
void Default_Card::increaseHealth(int amount)
{
	mBasicHealth += amount;
}


bool Default_Card::canAttack()
{
	return mCanAttack;
}


void Default_Card::removeHealth(int amount)
{
	mBasicHealth -= amount;
	mHealthSign.changeData(mBasicHealth);
	if (mBasicHealth <= 0) { mAlive = false; }
	std::cout << "Health left:" << mBasicHealth << std::endl;
	if (mAlive == false) { std::cout << "dead" << std::endl; }
}
bool Default_Card::isAlive()
{
	return mAlive;
}

eEffect Default_Card::getEffect()
{
	return mEffectType;
}
std::string Default_Card::getName()
{
	return mName;
}
int Default_Card::getHealth()
{
	return mBasicHealth;
}
int Default_Card::getAttack()
{
	return mBasicAttack;
}

void Default_Card::free()
{
	std::cout << "Deleting memory from:" << mName << std::endl;
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
		mPosX = 0;
		mPosY = 0;

		std::cout << "free.." << std::endl;
	}
	
	mHealthSign.free();
	mAPSign.free();
	mCostSign.free();
	HoverEffect.free();
	mFrame.free();
	mIcons.free();
	mBackground.free();
	
	

}