//
// @Author: Moritz Volkenandt (2017-)
// 
// Player-Deck(see Deck.hpp for more info)
//
#pragma once

#include "Deck.hpp"
#include <memory>

class Player_Field;
class Player_Hand;
class Opponent_Field;

class Player_Deck : public Deck
{
public:
	Player_Deck();
	Player_Deck(const std::weak_ptr<Player_Field> &field, const std::weak_ptr<Player_Hand> &hand);
	~Player_Deck();

	void createDeck() {};
	void createDeck(const std::weak_ptr<Opponent_Field>&field);

private:
	
};