#pragma once

#include "Opponent_Deck.hpp"
#include "Player_Field.hpp"
#include "Opponent_Field.hpp"
#include "Opponent_Hand.hpp"

#include "Hero.hpp"
#include "HeroHealth.hpp"
#include "Resource.hpp"

#include "Graveyard.hpp"

#include "Name.hpp"
//#include "CurrentTurn.hpp"

class Opponent
{
public:
	Opponent();
	~Opponent();

	void draw();
	void draw(int amount);

	void playCard();


	void update();
	void render();

	void play();

	void setAlpha(Uint8 alpha);

	//void setTurn(const std::shared_ptr<CurrentTurn> &turn);
	void setField(const std::shared_ptr<Player_Field> &field);
	void setHero(const std::shared_ptr<Hero>&hero);

	std::shared_ptr<Opponent_Field> getField();
	std::shared_ptr<Hero> getHero();

	bool wantsToEndTurn();
	bool isAlive();
	void setTurn();

	void free();
	

private:
	//std::shared_ptr<CurrentTurn> mTurn
	void startTurn();

	bool mItsMyTurn;
	bool mCardPlayed;
	bool mCanAttack;

	int mEndTurn;

	int mAttackStage;
	int mCurrentAttacker;
	int mCurrentTarget;

	bool endTurn;

	Name mName;
	std::shared_ptr<Opponent_Deck> mDeck;
	std::shared_ptr<Opponent_Hand> mHand;

	std::shared_ptr<Opponent_Field> mField;
	std::shared_ptr<Hero> mHero;
	std::shared_ptr<Graveyard> mGraveyard;
};