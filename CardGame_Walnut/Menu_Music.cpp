#include "Menu_Music.hpp"

#include <stdlib.h>
#include <time.h>

#include "GetFiles.hpp"
#include "draw.hpp"

#include <iostream>

enum {
	PAUSE = 0,
	STOP = 1,
	RESUME = 2,
	NEXT = 3,
	PREV = 4,
	MAX_BTN = 5
};
Menu_Music::Menu_Music()
{
	MusicBtn[NEXT].loadFromFile("Data/Menu/skip.png");
	MusicBtn[STOP].loadFromFile("Data/Menu/stop.png");
	MusicBtn[RESUME].loadFromFile("Data/Menu/resume.png");
	MusicBtn[PREV].loadFromFile("Data/Menu/prev.png");
	MusicBtn[PAUSE].loadFromFile("Data/Menu/pause.png");

	
	int x = 25;
	int y = 125;
	MusicBox = { x-10,y-70,300,110 };
	MusicBtn[PAUSE].setPos(x, y);
	MusicBtn[STOP].setPos(x + 40, y);
	MusicBtn[RESUME].setPos(x+80, y);
	MusicBtn[NEXT].setPos(x + 120, y);
	MusicBtn[PREV].setPos(x + 160, y);

	Intro.setPos(x, y-65);
	CurrentSong.setPos(x, y-35);
	GetFiles files;
	BMusicName = files.getFiles("Data/Music/menu/");

	for (int i = 0; i < BMusicName.size(); i++)
	{
		BMusic.push_back(Music(BMusicName.at(i)));
	}
	start();
}


Menu_Music::~Menu_Music()
{
	BMusic.at(CurrentSongIndex).stop();
	
	for (auto i : BMusic)
		i.free();
}


void Menu_Music::update()
{
	for (int i = 0; i < MAX_BTN; i++)
		if (MusicBtn[i].IsPressed())
			callButton(i);
}

void Menu_Music::render()
{
	Intro.render();
	CurrentSong.render();

	MusicBtn[NEXT].render();
	MusicBtn[PREV].render();
	MusicBtn[STOP].render();
	MusicBtn[PAUSE].render();
	MusicBtn[RESUME].render();


	drawRect(MusicBox);

}

void Menu_Music::stop()
{
	BMusic.at(CurrentSongIndex).pause();
}

void Menu_Music::start()
{
	srand(time(nullptr));
	int i = rand() % BMusic.size();
	BMusic.at(i).start();

	std::string intro = "Playing:";
	Intro.loadFromRenderedText(intro);
	CurrentSong.loadFromRenderedText(BMusicName.at(i));
	CurrentSongIndex = i;
}

void Menu_Music::callButton(int btn)
{
	switch (btn)
	{
	case(PAUSE):
		BMusic.at(CurrentSongIndex).pause();
		break;
	case(STOP):
		BMusic.at(CurrentSongIndex).stop();
		break;
	case(RESUME):
		BMusic.at(CurrentSongIndex).start();
		break;
	case(NEXT):
		CurrentSongIndex++;
		BMusic.at(CurrentSongIndex - 1).stop();
		if (CurrentSongIndex < BMusic.size())
		{
			BMusic.at(CurrentSongIndex).start();
			CurrentSong.loadFromRenderedText(BMusicName.at(CurrentSongIndex));
		}
		else
		{
			CurrentSongIndex = 0;
			BMusic.at(CurrentSongIndex).start();
			CurrentSong.loadFromRenderedText(BMusicName.at(CurrentSongIndex));
		}
		break;
	case(PREV):
		//todo
		break;
	}
}
