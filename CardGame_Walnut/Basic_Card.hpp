#pragma once

#include <memory>

#include "DefaultTexture.hpp"
#include "StatsSign.hpp"

#include "ePosition.hpp"
#include "Hover_Card.hpp"

#include "Effects.hpp"

#include "Frame.hpp"
#include "Icons.hpp"
#include "Rarity.hpp"

class Field;
class Hand;
class Deck;
class Place;

class Basic_Card : public DefaultTexture
{
public:
	Basic_Card() = default;

	virtual void render(bool &hoverIsActive, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {};
	virtual void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {};
	virtual void renderHoverEffect();
	virtual void renderBackside(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {};

	virtual bool activateEffect() { return false; };

	bool setStuff(const std::weak_ptr<Deck> &deck, const std::weak_ptr<Hand> &hand, const std::weak_ptr<Field> &field, const std::weak_ptr<Field> &oppfield);

	virtual void play(const std::shared_ptr<Field> &Field) {}; //Default|Effect Card, Parameter->Field,Hand,Deck? superclass needed?
	void changePosition(Position newpos);

	void move(int x, int y); //move -> mPosX+=x; mPosY+=y;
	virtual void moveSigns(int x,int y) {};
	virtual void setPos(int x, int y) {}; //mPosX = x; mPosY = y;

	//Player wants to move card?(hand) 
	virtual void setActive();
	virtual void setInactive();
	virtual bool isActive();

	virtual bool MouseIsAbove();

	void increaseCost(int amount);

	int getCost();

protected:
	DefaultTexture mBackground;

	Hover_Card HoverEffect;
	Frame mFrame;
	Icons mIcons;
	Rarity mRarity = Rarity::Bronze; //add later with Lua


	bool mActive;

	std::string mName;
	std::string mPath; // texture path
	int mBasicCost;
	int mCurrentCost;
	StatsSign mCostSign;

	Position mPos = Position::DECK; //wegen der AI

	std::unique_ptr<Effects> mEffect = nullptr;
};