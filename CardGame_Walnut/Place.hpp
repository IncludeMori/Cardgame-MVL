#pragma once

#include <vector>

#include "BaseCard.hpp"
#include "Graveyard.hpp"

class Place
{
public:
	Place();
	~Place();

	virtual int getSize() { return mSize; }

protected:
	int mSize;

	std::vector<std::shared_ptr<BaseCard>> mCard;
	std::vector<std::shared_ptr<BaseCard>>::iterator mCardIt;

	std::shared_ptr<Graveyard> mGraveyard;
};

