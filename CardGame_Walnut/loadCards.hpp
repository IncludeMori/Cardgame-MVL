#pragma once


#include <vector>
#include <memory>

#include "Default_Card.hpp"

class loadCards
{
public:
	loadCards();
	~loadCards();

	void load(std::vector<std::unique_ptr<Default_Card>> &cards);
};

