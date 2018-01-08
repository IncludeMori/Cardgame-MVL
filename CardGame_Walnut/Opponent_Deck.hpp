#pragma once

#include "Deck.hpp"

class Opponent_Field;
class Opponent_Hand;

class Opponent_Deck : public Deck
{
public:
	Opponent_Deck();
	Opponent_Deck(const std::shared_ptr<Opponent_Field> &field, const std::shared_ptr<Opponent_Hand> &hand);
	~Opponent_Deck();

private:
};