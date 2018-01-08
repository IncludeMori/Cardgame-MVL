#pragma once

#include "Who.hpp"

#include <SDL.h>
#include <string>
#include <memory>

#include "Player.hpp"
#include "Opponent.hpp"

class CurrentTurn
{
public:
	CurrentTurn();
	CurrentTurn(Who x); // player -> first turn?
	CurrentTurn(Who x,std::shared_ptr<Player> player, std::shared_ptr<Opponent> opp);

	void update();
	void render(double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void endTurn();

	void deactivate();
	void activate();

	void setAlpha(Uint8 alpha);

	bool isPlayersTurn();
	bool isPressed();

	int getTurn();

	void free();

private:
	bool isActive;
	SDL_Texture *mTexture;

	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Opponent> mOpponent;

	int mPosX, mPosY, mWidth, mHeight;
	int mTurnNumber;

	bool loadFromFile(std::string path);

	bool mTurn[2];
};