//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: SDL_texture for cards
//
#pragma once

#include <string>
#include <memory>

#include "BoostCard.hpp"
#include "ePosition.hpp"
#include "BaseCard.hpp" 
#include "StatsSign.hpp"
#include "Card_Effects.hpp"
#include "Hover_Card.hpp"

class MonsterCard : public BaseCard, public std::enable_shared_from_this<MonsterCard>
{
public:
	MonsterCard(std::string &path, int x);
	MonsterCard(int Health, int Attack, int Type, std::string &path);
	~MonsterCard();

	void play(const std::shared_ptr<Field> &Field);

	void update();
	void updateStats();

	void render(bool &hoverIsActive, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) override;
	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) override;
	void renderCardback(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) override;
	void loadTexture();
	
	bool mouseIsAbove();

	void moveSigns(int x, int y); //move -> mPosX+=x; mPosY+=y;
	void setPos(int x, int y); //mPosX = x; mPosY = y;

	bool activateEffect();

	void increase(eStat stat, int amount);
	void increaseHealth(int amount);
	void increaseAtk(int amount);

	bool canAttack();

	void removeHealth(int amount);
	bool isAlive(); // returns true if health >0

	void setHover(bool& b);

	eEffect getEffect();
	std::string getName();
	int getHealth();
	int getAttack();

protected:
	StatsSign mHealthIcon;
	StatsSign mApIcon;

	eEffect mEffectType = eEffect::ERROR;
	int mBasicHealth;
	int mCurrentHealth;
	int mBasicAttack;
	int mCurrentAttack;
	bool mAlive;
	bool mCanAttack;

	bool mTimerActive = false;
	SDL_TimerID myTimer;

	void renderIcons();
};