#include "Player.hpp"

#include <iostream>
Player::Player()
{
	mName.init(who::type::PLAYER, "Player 1");
	mFieldEffectActive = false;

	mHealth = 40;
	mAlive = true;
	
	mHand.reset(new Player_Hand());
	mField.reset(new Player_Field);
	mHeroPortrait.reset(new Hero(0,mHealth));
	mDeck.reset(new Player_Deck(mField,mHand));
	mGraveyard.reset(new Graveyard());
	mGraveyard->init(0);

	mHand->setGraveyard(mGraveyard);
	mField->setGraveyard(mGraveyard);
}

Player::~Player()
{
	free();
}

bool Player::update()
{
	if (!mFieldEffectActive) //solange ein Effekt aktiv ist wird die Hand deaktiviert
		mHand->update(mField);
	if (!isMovingAHandCard()) {
		if (!mField->update()) { mFieldEffectActive = true; }
		else
			mFieldEffectActive = false;
	}
	return mFieldEffectActive;
}

void Player::render()
{
	mName.render();
	mGraveyard->render();
	mField->render();
	mDeck->render();
	//mResource.render();
	mHeroPortrait->render();
	mHand->render();
}

void Player::startTurn()
{
	drawCard();
	mHand->startTurn();
}

void Player::increaseHealth(int amount)
{
	mHealth += amount;
}

void Player::decreaseHealth(int amount)
{
	mHealth -= amount;
	mHeroPortrait->dealDmg(amount);

	if (mHealth <= 0)
	{
		mAlive = false;
	}
}

bool Player::modifyHealth(int amount)
{
	mHealth += amount;
	if (amount <= 0) {
		mHeroPortrait->dealDmg(amount);
		if (mHealth <= 0) {
			mAlive = false;
			return false;
		}
	}
	return true;
}

bool Player::isAlive()
{
	return mAlive;
}

void Player::drawCard()
{
	static int amount = 1;
	std::cout << "Player draws card" << std::endl;
	if (!mHand->drawCard(mDeck->getNextCard()))
	{
		std::cout << "Player: no card left. Dmg: " << amount << std::endl;
		decreaseHealth(amount++);
	}
}

void Player::discardCard()
{
	
}

void Player::drawStartHand()
{
	for (int i = 0; i < 6; i++)
	{
		drawCard();
	}
}

bool Player::isMovingAHandCard()
{
	return mHand->isUsingACard();
}

void Player::setField(const std::weak_ptr<Opponent_Field>&field)
{
	mField->setField(field);

	if (field.lock() == nullptr)
		__debugbreak();
	mDeck->createDeck(field);
	drawStartHand();
	
}
void Player::setHero(const std::weak_ptr<Hero>&hero)
{
	mField->setHero(hero);
}

void Player::setAlpha(Uint8 alpha)
{
	mDeck->setAlpha(alpha);
	mHeroPortrait->setAlpha(alpha);
}

std::weak_ptr<Player_Field> Player::getField()
{
	return mField;
}

std::weak_ptr<Hero> Player::getHero()
{
	return mHeroPortrait;
}

void Player::free()
{
	//mDeck.free();
	//mHand.free();
	//mHeroPortait
	//mField->free();
}