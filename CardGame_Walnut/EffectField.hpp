#pragma once

#include <memory>

#include "EffectCard.hpp"

class EffectField
{
public:
	EffectField();
	~EffectField();

	bool add(const std::shared_ptr<BaseCard> &card);
	bool checkEffect();

	void render();

	void reset();

protected:
	std::shared_ptr<BaseCard> LastUsedCard = nullptr;

};

