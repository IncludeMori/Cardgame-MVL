#include "CurrentTurn.hpp"
#include <iostream>
#include <SDL_image.h>
#include "gScreenSize.hpp"
#include "gMouse.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

using namespace who;

CurrentTurn::CurrentTurn()
{
	isActive = true;
	mTurnNumber = 1;
	mTexture = nullptr;
	loadFromFile("Data/end_turn.png");
	mHeight = mHeight / 2;
	mPosX = SCREEN_WIDTH - mWidth * 1.5;
	mPosY = SCREEN_HEIGHT / 2 - mHeight / 2;
}
CurrentTurn::CurrentTurn(who::type x) : CurrentTurn()
{
	if (x == PLAYER)
	{
		mIsOpponentsTurn = false;
	}
	else
	{
		mIsOpponentsTurn = true;
	}
}
CurrentTurn::CurrentTurn(who::type x, std::shared_ptr<Player> player, std::shared_ptr<Opponent> opp) : CurrentTurn(x)
{
	mPlayer = player;
	mOpponent = opp;
}

void CurrentTurn::update()
{
	if (isActive)
	{
		if (isPressed() && !mIsOpponentsTurn)
		{
			endTurn();
		}
		else if (mOpponent->wantsToEndTurn() && mIsOpponentsTurn)
		{
			endTurn();
			mOpponent->setTurn();
		}
	}
}
void CurrentTurn::render(SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mWidth, mHeight };

	SDL_Rect dclip{ 0,0,mWidth,mHeight };
	if (!mIsOpponentsTurn) { dclip.y = 0; }
	else { dclip.y = mHeight; }



	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &dclip, &renderQuad, angle, center, flip); // renders texture to screen

}

void CurrentTurn::endTurn()
{
	if (mIsOpponentsTurn)
	{
		mIsOpponentsTurn = false;
		mPlayer->startTurn();
	}
	else
	{
		mIsOpponentsTurn = true;
	}
	mTurnNumber++;
}

void CurrentTurn::deactivate()
{
	isActive = false;
}

void CurrentTurn::activate()
{
	isActive = true;
}

bool CurrentTurn::isPlayersTurn()
{
	return !mIsOpponentsTurn;
}

bool CurrentTurn::isPressed()
{
	if (gMouse.getX() > mPosX && gMouse.getX() < mPosX + mWidth &&
		gMouse.getY() > mPosY && gMouse.getY() < mPosY + mHeight &&
		gMouse.isPressed())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CurrentTurn::getTurn()
{
	return mTurnNumber;
}