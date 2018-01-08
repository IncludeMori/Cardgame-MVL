#include "CurrentTurn.hpp"
#include <iostream>
#include "gRenderer.hpp"
#include <SDL_image.h>
#include "gScreenSize.hpp"
#include "gMouse.hpp"

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
void CurrentTurn::render(double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mWidth, mHeight };

	SDL_Rect clip{ 0,0,mWidth,mHeight };
	if (mTurn[PLAYER] == true) { clip.y = 0; }
	else { clip.y = mHeight; }



	SDL_RenderCopyEx(gRenderer, mTexture, &clip, &renderQuad, angle, center, flip); // renders texture to screen

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
		SDL_SetTextureAlphaMod(mTexture, alpha);

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
void CurrentTurn::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
		mPosX = 0;
		mPosY = 0;
	}
}

bool CurrentTurn::loadFromFile(std::string path)
{
	std::cout << "Loading: " << path << std::endl;

	//delete preexisting textures
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//neutral colorkey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	std::cout << mTexture << std::endl;
	return mTexture != NULL;
}