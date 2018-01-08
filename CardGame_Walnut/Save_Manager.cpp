#include "Save_Manager.hpp"
#include <iostream>


Save_Load::Save_Load(const int amount)
{
	TOTAL_DATA = amount;

	mData = new Sint32[TOTAL_DATA];

}

Save_Load::~Save_Load()
{
	delete[] mData;
	mData = NULL;

	close();

}

void Save_Load::open()
{

	//Open file for reading in binary
	SDL_RWops* file = SDL_RWFromFile("name.bin", "r+b");


	//File does not exist
	if (file == NULL)
	{
		std::cout << "Unable to open file: " << SDL_GetError();

		//create a new file
		file = SDL_RWFromFile("name.bin", "w+b");

		if (file != NULL)
		{
			std::cout << "New file created" << std::endl;

			//Initialize data
			for (int i = 0; i < TOTAL_DATA; ++i)
			{
				mData[i] = 0;
				SDL_RWwrite(file, &mData[i], sizeof(Sint32), 1);
			}

			//Close file handler
			SDL_RWclose(file);
		}
		else
		{
			std::cout << "Unable to create file: " << SDL_GetError() << std::endl;

		}
	}
	//File exists
	else
	{
		//Load data
		printf("Reading file...!\n");
		for (int i = 0; i < TOTAL_DATA; ++i)
		{
			SDL_RWread(file, &mData[i], sizeof(Sint32), 1);
		}

		//Close file handler
		SDL_RWclose(file);
	}

	/*
	//Initialize data textures
	gDataTextures[0].loadFromRenderedText(std::to_string((_Longlong)mData[0]), highlightColor);
	for (int i = 1; i < TOTAL_DATA; ++i)
	{
	gDataTextures[i].loadFromRenderedText(std::to_string((_Longlong)mData[i]), textColor);
	}
	*/


}


void Save_Load::close()
{
	//Open data for writing
	SDL_RWops* file = SDL_RWFromFile("name.bin", "w+b");
	if (file != NULL)
	{
		//Save data
		for (int i = 0; i < TOTAL_DATA; ++i)
		{
			SDL_RWwrite(file, &mData[i], sizeof(Sint32), 1);
		}

		//Close file handler
		SDL_RWclose(file);
	}
	else
	{
		printf("Error: Unable to save file! %s\n", SDL_GetError());
	}
}


void Save_Load::save(Sint32 Data, int number)
{
	mData[number] = Data;
}


Sint32 Save_Load::getData(int number)
{
	return mData[number];
}