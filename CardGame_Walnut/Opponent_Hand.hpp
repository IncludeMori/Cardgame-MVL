#pragma once

#include "gScreenSize.hpp"

#include "Hand.hpp"


class Opponent_Hand : public Hand
{
public:
	Opponent_Hand();

	std::shared_ptr<Basic_Card> getBestCard();
	bool canPlayCard();

	void render();

private:

};