#pragma once


#include <vector>
#include <memory>

#include "MonsterCard.hpp"

class loadCards
{
public:
	loadCards();
	~loadCards();

	void load(std::vector<std::unique_ptr<MonsterCard>> &cards);
};

