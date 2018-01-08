#pragma once

#include <memory>

#include "Effect_Card.hpp"

class EffectField
{
public:
	EffectField();
	~EffectField();

	bool add(const std::shared_ptr<Basic_Card> &card);
	bool checkEffect();

	void render();

	void reset();

protected:
	std::shared_ptr<Basic_Card> LastUsedCard = nullptr;

};

