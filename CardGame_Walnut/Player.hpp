//
// @Author: Moritz Volkenandt (2017-)
// 
// player data
//
#pragma once

#include "Player_Deck.hpp"
#include "Player_Hand.hpp"
#include "GameField.hpp"
#include "Resource.hpp"

#include "Hero.hpp"
#include "HeroHealth.hpp"

#include "Turn_Enum.hpp"

#include "Graveyard.hpp"



class Player
{
public:
	Player();
	~Player();

	bool update();
	void render();

	void startTurn();

	void increaseHealth(int amount);
	void decreaseHealth(int amount);

	bool isAlive();

	void drawCard();
	void discardCard();

	bool isMovingAHandCard();

	void setAlpha(Uint8 alpha);

	//Opponent Field/+Hero
	void setField(const std::shared_ptr<Opponent_Field>&field);
	void setHero(const std::shared_ptr<Hero>&hero);

	std::shared_ptr<Player_Field> getField();
	std::shared_ptr<Hero> getHero();
	
	void free();

private:
	int mHealth;
	bool mAlive;

	bool field_battlecry_active = false;

	std::shared_ptr<Player_Hand> mHand;  //hand [first 4 cards from "mDeck"]
	std::shared_ptr<Player_Deck> mDeck;
	std::shared_ptr<Hero> mHeroPortrait;
	std::shared_ptr<Player_Field> mField;
	std::shared_ptr<Graveyard> mGraveyard;

	void drawStartHand();
};
