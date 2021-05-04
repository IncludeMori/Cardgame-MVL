#pragma once

#include <memory>
#include <vector>

#include "GameObj.hpp"
#include "StatsSign.hpp"

#include "ePosition.hpp"
#include "Hover_Card.hpp"

#include "Effects.hpp"

#include "Frame.hpp"
#include "Icons.hpp"
#include "Rarity.hpp"

#include <boost/filesystem.hpp>

class Field;
class Hand;
class Deck;
class Place;

class BaseCard : public GameObj
{
public:
	BaseCard() = default;
	BaseCard(int x, int y) : GameObj(x, y) {};
	BaseCard(const std::string &path, int x = 0, int y = 0) : GameObj(x,y,path) {};

	using GameObj::render;
	virtual void render(bool &hoverIsActive, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) {};

	virtual void update();

	virtual void renderHoverEffect();
	virtual void renderCardback(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) {};

	virtual bool activateEffect() { return false; };

	bool setStuff(const std::weak_ptr<Deck> &deck, const std::weak_ptr<Hand> &hand, const std::weak_ptr<Field> &field, const std::weak_ptr<Field> &oppfield);

	virtual void play(const std::shared_ptr<Field> &Field) {}; //Default|Effect Card, Parameter->Field,Hand,Deck? superclass needed?
	void changePlacePosition(Position newpos);

	void move(int x, int y) override; 

	virtual void moveSigns(int x,int y) {};

	//Player wants to move card -> only one card can be active at a time 
	virtual void setActive();
	virtual void setInactive();
	virtual bool isActive();

	//used for the enlarged card after the mouse stays above a card for a specified amount of time
	virtual void setHover(bool &b) {};

	virtual bool mouseIsAbove();

	void modifyCost(int amount);
	int getCost();

protected:
	std::string mName;
	std::string mTexturePath;
	int mBasicPlayCost;
	int mCurrentPlayCost;
	bool mActive;

	std::vector<int> mBaseStats; 
	std::vector<int> mCurrentStats; 

	std::vector<StatsSign> mStatsIcon; 
	StatsSign mCostIcon;
	DefaultTexture mBackground;
	Frame mFrame;
	Icons mIcon;

	Rarity mRarity = Rarity::Bronze; 
	Position mPlacePosition = Position::DECK; //AI

	HoverCardEffect mHoverEffectTexture;

	std::unique_ptr<Effects> mEffect = nullptr;
};