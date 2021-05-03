#include "EffectField.hpp"

#include "gScreenSize.hpp"

EffectField::EffectField()
{
}


EffectField::~EffectField()
{
}


bool EffectField::add(const std::shared_ptr<BaseCard> &card)
{
	LastUsedCard = card;
	LastUsedCard->setPos(87,SCREEN_HEIGHT/2-LastUsedCard->getHeight()/2);

	return LastUsedCard->activateEffect();
}

bool EffectField::checkEffect()
{
	return LastUsedCard->activateEffect();
}

void EffectField::render()
{
	if (LastUsedCard != nullptr) 
		LastUsedCard->render();
}

void EffectField::reset()
{
	LastUsedCard.reset();
	LastUsedCard = nullptr;
}
