#include "NumberPopup.hpp"



#include <iostream>
#include <String>

#include "Renderer.hpp"
using namespace sdl2_Renderer;

NumberPopup::NumberPopup()
{
	loadNumberTexture();
	mNumberBackground.loadFromFile("Data/peng.png");

}
NumberPopup::~NumberPopup()
{

}

void NumberPopup::render()
{
	update();
	

	for (unsigned int i = 0; i < mStat.size(); i++)
	{
		mNumberBackground.setPos(mPosX.at(i)-15,mPosY.at(i));
		CurrentNumbers.setPos(mPosX.at(i)+23, mPosY.at(i)+30);
		CurrentNumbers.changeData(mStat.at(i));
		
		mNumberBackground.render();
		CurrentNumbers.render();
	}

	
}
void NumberPopup::update()
{
	if (mStat.size() < myTimer.size())
	{
		myTimer.erase(myTimer.begin());
		mPosX.erase(mPosX.begin());
		mPosY.erase(mPosY.begin());
	}

}

Uint32 my_callbackfunc2(Uint32 interval, void *param)
{
	
	if (static_cast<std::vector<int>*>(param)->size() > 0)
	static_cast<std::vector<int>*>(param)->erase(static_cast<std::vector<int>*>(param)->begin());
	return 0;
}

void NumberPopup::add(int amount, int posX, int posY) //game obj übergeben?
{
	update();
	
	posX = posX + 30;
	posY = posY + 50;


	std::cout << "Start timer" << std::endl;
	
	myTimer.push_back(SDL_AddTimer(2500, my_callbackfunc2, &mStat));//start new thread as timer
	mPosX.push_back(posX);
	mPosY.push_back(posY);
	mStat.push_back(amount);
	//SDL_RemoveTimer(myTimer);
	//mTimerActive = true;
	//mNumberBackground.setPos(posX, posY);
}

void NumberPopup::free()
{
	//todo
}

bool NumberPopup::loadNumberTexture()
{
	std::string path = "Data/numbers.png";
	std::cout << "Loading: " << path << std::endl;
	//delete preexisting textures
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//neutral colorkey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer.get(), loadedSurface);
		if (newTexture == nullptr)
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
	mNumberTexture = newTexture;
	return mNumberTexture != nullptr;
}
