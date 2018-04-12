#include "CurrentTurn.hpp"
#include <iostream>
#include <SDL_image.h>
#include "gScreenSize.hpp"
#include "gMouse.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

CurrentTurn::CurrentTurn()
{
	isActive = true;
	mTurn[PLAYER] = true;
	mTurn[OPPONENT] = false;

	loadFromFile("Data/end_turn.png");
	mHeight = mHeight / 2;
	mPosX = SCREEN_WIDTH - mWidth*1.5;
	mPosY = SCREEN_HEIGHT / 2 - mHeight / 2;
}
CurrentTurn::CurrentTurn(Who x,std::shared_ptr<Player> player, std::shared_ptr<Opponent> opp)
{
	isActive = true;
	mTurnNumber = 1;
	mTexture = nullptr;
	loadFromFile("Data/end_turn.png");
	mHeight = mHeight / 2;
	mPosX = SCREEN_WIDTH - mWidth*1.5;
	mPosY = SCREEN_HEIGHT / 2 - mHeight / 2;

	if (x == PLAYER)
	{
		mTurn[PLAYER] = true;
		mTurn[OPPONENT] = false;
	}
	else
	{
		mTurn[PLAYER] = false;
		mTurn[OPPONENT] = true;
	}

	mPlayer = player;
	mOpponent = opp;

}
CurrentTurn::CurrentTurn(Who x)
{
	isActive = true;
	mTurnNumber = 1;
	mTexture = nullptr;
	loadFromFile("Data/end_turn.png");
	mHeight = mHeight / 2;
	mPosX = SCREEN_WIDTH - mWidth*1.5;
	mPosY = SCREEN_HEIGHT / 2 - mHeight / 2;

	if (x == PLAYER)
	{
		mTurn[PLAYER] = true;
		mTurn[OPPONENT] = false;
	}
	else
	{
		mTurn[PLAYER] = false;
		mTurn[OPPONENT] = true;
	}
}

void CurrentTurn::update()
{
	if (isActive)
	{
		if (isPressed() && mTurn[PLAYER] == true)
		{
			endTurn();
		}
		else if (mOpponent->wantsToEndTurn() && mTurn[OPPONENT] == true)
		{
			endTurn();
			mOpponent->setTurn();
		}
	}
}
void CurrentTurn::render(SDL_Rect *clip,double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mWidth, mHeight };

	SDL_Rect dclip{ 0,0,mWidth,mHeight };
	if (mTurn[PLAYER] == true) { dclip.y = 0; }
	else { dclip.y = mHeight; }



	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), &dclip, &renderQuad, angle, center, flip); // renders texture to screen

}

void CurrentTurn::endTurn()
{
	if (mTurn[OPPONENT] == true)
	{
		mTurn[PLAYER] = true;
		mPlayer->startTurn();

		mTurn[OPPONENT] = false;
		
		
	}
	else
	{
		mTurn[PLAYER] = false;
		mTurn[OPPONENT] = true;

		
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

void CurrentTurn::setAlpha(Uint8 alpha)
{
	if (mTexture != nullptr)
		SDL_SetTextureAlphaMod(mTexture.get(), alpha);

}

bool CurrentTurn::isPlayersTurn()
{
	return mTurn[PLAYER];
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