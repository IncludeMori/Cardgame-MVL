#pragma once



#include "Player_Field.hpp"
#include "Opponent_Field.hpp"

#include "Hero.hpp"

class Game_Field
{
public:
	Game_Field();
	~Game_Field();

	void updateT();
	void render();
	

private:
	int mActiveCard = 0;

	Hero mPlayerPortrait{ 0,40 };
	Hero mOppPortrait{ 1,40 };

	Arrow mAttackCard;
	Arrow mAttackTarget;

	Player_Field mPlayerField;

};