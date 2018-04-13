#pragma once

#include "Who.hpp"

#include <SDL.h>
#include <string>
#include <memory>

#include "Player.hpp"
#include "Opponent.hpp"

#include "GameObj.hpp"

class CurrentTurn : public GameObj
{
public:
	CurrentTurn();
	CurrentTurn(who::type x);
	CurrentTurn(who::type x, std::shared_ptr<Player> player, std::shared_ptr<Opponent> opp);

	void update();
	void render(SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

	void endTurn();

	void deactivate();
	void activate();

	bool isPlayersTurn();
	bool isPressed();

	int getTurn();

private:
	bool isActive;

	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Opponent> mOpponent;

	int mTurnNumber;

	bool mIsOpponentsTurn = false;
};