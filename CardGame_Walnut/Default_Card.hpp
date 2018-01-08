//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: SDL_texture for cards
//
#pragma once

#include "BoostCard.hpp"

#include "ePosition.hpp"
#include "Basic_Card.hpp" //
#include <string>
#include <memory>
#include "StatsSign.hpp"

#include "Card_Effects.hpp"
#include "Hover_Card.hpp"



class Default_Card : public Basic_Card, public std::enable_shared_from_this<Default_Card>
{
public:
	Default_Card();
	Default_Card(std::string &path);
	Default_Card(std::string &path, int x);
	Default_Card(int Health, int Attack, int Type, std::string &path);
	~Default_Card();

	void play(const std::shared_ptr<Field> &Field);

	void update();
	void updateStats();
	void render(bool &hoverIsActive, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) ;
	void renderBackside(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void loadTexture();
	
	bool MouseIsAbove();

	void moveSigns(int x, int y); //move -> mPosX+=x; mPosY+=y;
	void setPos(int x, int y); //mPosX = x; mPosY = y;

	bool activateEffect();

	void increase(eStat stat, int amount);
	void increaseHealth(int amount);
	void increaseAtk(int amount);

	bool canAttack();

	void removeHealth(int amount);
	bool isAlive(); // returns true if health >0

	eEffect getEffect();
	std::string getName();

	int getHealth();
	int getAttack();

	void free();

protected:
	StatsSign mHealthSign;
	StatsSign mAPSign;
	void renderSigns();

	bool mCanAttack;

	bool mTimerActive = false;
	SDL_TimerID myTimer;
	
	//stats
	eEffect mEffectType = eEffect::ERROR;
	int mBasicHealth;
	int mCurrentHealth;

	int mBasicAttack;
	int mCurrentAttack;

	bool mAlive;
};