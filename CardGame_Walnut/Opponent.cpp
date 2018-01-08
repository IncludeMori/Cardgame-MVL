#include "Opponent.hpp"


Opponent::Opponent()
{
	int mHealth = 40;
	mField.reset(new Opponent_Field);
	mHero.reset(new Hero(1,mHealth));
	mHand.reset(new Opponent_Hand());
	mEndTurn = false;
	mItsMyTurn = false;
	mCardPlayed = false;
	mCanAttack = true;
	mAttackStage = -1;
	mGraveyard.reset(new Graveyard());
	endTurn = false;

	mDeck.reset(new Opponent_Deck(mField, mHand));
	mDeck->createDeck();
	
	mHand->setGraveyard(mGraveyard);
	mField->setGraveyard(mGraveyard);
	draw(4);
}
Opponent::~Opponent()
{
}

void Opponent::draw()
{
	static int amount = 1;

	if (!mHand->drawCard(mDeck->getNextCard()))
	{
		mHero->dealDmg(amount++);
	}
}

void Opponent::draw(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		mHand->drawCard(mDeck->getNextCard());
	}
}

void Opponent::playCard()
{
	if (mField->hasSpace())
	{
		mField->addCard(mHand->getBestCard());
	}
	else
	{
		std::cout << "Opp Field has no space left" << std::endl;
	}
}

void Opponent::update()
{
	mField->update();
	
}
void Opponent::render()
{
	mGraveyard->render();
	mHero->render();
	mDeck->render();
	mField->render();
	mHand->render();
	
}

void Opponent::play()
{
	//start turn
    // next frame start playing a card -> move card (only Hand to field)
	// attack mit arrow and X animation


	if (!mItsMyTurn)
	{ 
		startTurn();
	} //draw card, get resources, once per turn

	else if (!mCardPlayed) {

		if (!mField->isFull()) {
			while (mHand->canPlayCard() && !mField->isFull())
			{
				playCard();
			}
		}
		mCardPlayed = true;
	}
	else
	{
		mItsMyTurn = false;
		mCardPlayed = false;
		mEndTurn = true;
		endTurn = true;
		
	}
}

void Opponent::setAlpha(Uint8 alpha)
{
	mDeck->setAlpha(alpha);
	mHero->setAlpha(alpha);

}

//void Opponent::setTurn(const std::shared_ptr<CurrentTurn> &turn)
//{
//	mTurn = turn;
//}
void Opponent::setField(const std::shared_ptr<Player_Field>& field)
{
	//mField->setField(field);
	
}
void Opponent::setHero(const std::shared_ptr<Hero>&hero)
{
	mField->setHero(hero);
}

std::shared_ptr<Opponent_Field> Opponent::getField()
{
	return mField;
}

std::shared_ptr<Hero> Opponent::getHero()
{
	return mHero;
}

bool Opponent::wantsToEndTurn()
{
	return endTurn;
}
bool Opponent::isAlive()
{
	return mHero->isAlive();
}

void Opponent::setTurn()
{
	endTurn = false;
}
void Opponent::startTurn()
{
	std::cout << "Opponent starts turn" << std::endl;
	mHand->startTurn();
	draw();
	mItsMyTurn = true;
}

void Opponent::free()
{
	//mField->free();
	//mDeck.free();
	//mHand.free();
}