#pragma once

#include "Default_Card.hpp"
#include "Player_deck.hpp"
#include "Player_Field.hpp"
#include "Hand.hpp"
#include "Resource.hpp"

#include <vector>
#include "gScreenSize.hpp"
#include <memory>

//shared ptr für hand

class Player_Hand : public Hand
{
public:
	Player_Hand();
	~Player_Hand();

	void startTurn();

	void update(const std::shared_ptr<Player_Field> &mField);

	bool isPlayable(int index);
	void played(int index);

private:

};