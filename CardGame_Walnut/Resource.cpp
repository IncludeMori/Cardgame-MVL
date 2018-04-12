#include "Resource.hpp"


#include <iostream>
#include "gScreenSize.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

Resource::Resource()
{
	mCurrentStat = 0;
	mBaseStat = 0;

	mBackground.loadFromFile("Data/Hero_Interface/Background_AmountMana.png");
	loadFromFile("Data/numbers.png");
	mWidth = 35;
	mHeight = 35;
	
}

void Resource::removeAv(int amount)
{
	mCurrentStat -= amount;

	mEnergyInterface.subEnergy(amount);
}

void Resource::setPos(int x, int y, int who)
{
	setPos(x, y-10);
	mBackground.setPos(x-5, y - 22);
	mEnergyInterface.init(who);
}

void Resource::increase()
{
	mBaseStat++;
	if (mBaseStat > 10) { mBaseStat = 10; }
	mCurrentStat = mBaseStat;

	mEnergyInterface.increase();

}
void Resource::decrease()
{
	mBaseStat--;
	if (mBaseStat < 0) { mBaseStat = 0; }

	mEnergyInterface.decrease();
}

void Resource::render(double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	mBackground.render();
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mHeight, mWidth };

	if (mCurrentStat < 10)
	{
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[mCurrentStat], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += 20;
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[11], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += 20;
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[mBaseStat], &renderQuad, angle, center, flip); // renders texture to screen
	}
	// 9 < x < 100
	else if (mCurrentStat == 10) {

		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[1], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += 30;
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[0], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += 15;
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[11], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += 15;
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[1], &renderQuad, angle, center, flip); // renders texture to screen
		renderQuad.x += 30;
		SDL_RenderCopyEx(Renderer.get(), mTexture, &mNumbers[0], &renderQuad, angle, center, flip); // renders texture to screen

	}


	mEnergyInterface.render();

}


int Resource::getAmount()
{
	return mBaseStat;
}
int Resource::getAvailable()
{
	return mCurrentStat;
}