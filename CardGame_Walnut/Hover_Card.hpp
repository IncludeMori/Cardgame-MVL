#pragma once

#include "DefaultTexture.hpp"

#include "Name_Plate.hpp"
#include "Frame.hpp"
#include "Icons.hpp"

#include "Rarity.hpp"

#include "Effect_Description.hpp"
#include "StatsSign.hpp"


class HoverCardEffect : public DefaultTexture
{
public:
	HoverCardEffect();
	HoverCardEffect(std::string &name,int health,int atk, int cost, Rarity rarity);
	HoverCardEffect(std::string& name, int cost, Rarity rarity);

	void update();
	void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void enable();
	void disable();

	bool isActive();

	void setStats(std::string& name, int cost, Rarity rarity);
	void setStats(std::string &name, int health, int atk, int cost, Rarity rarity);
	void setEffect(std::vector<std::string> &effects);


private:
	bool mIsActive = false;
	int mCost = 0, mHealth = 0, mAttack = 0;
	Rarity mRarity = Rarity::Undefined;

	StatsSign mSCost{ Stats_Size::HOVER }, mSHealth{ Stats_Size::HOVER }, mSAttack{ Stats_Size::HOVER };

	//Interface
	Frame mFrame;
	Icons mIcon;

	Name_Plate mNameplate;
	Effect_Description mEffectDescr;
};

