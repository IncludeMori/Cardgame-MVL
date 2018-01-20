#include "Menu_Music.hpp"

#include <stdlib.h>
#include <time.h>

#include "GetFiles.hpp"
#include "draw.hpp"

Menu_Music::Menu_Music()
{
	NextBtn.loadFromFile("Data/Menu/skip.png");
	StopBtn.loadFromFile("Data/Menu/stop.png");
	ResumeBtn.loadFromFile("Data/Menu/resume.png");
	PrevBtn.loadFromFile("Data/Menu/prev.png");
	PauseBtn.loadFromFile("Data/Menu/pause.png");

	
	int x = 25;
	int y = 100;
	MusicBox = { x-10,y-70,300,110 };
	PauseBtn.setPos(x, y);
	StopBtn.setPos(x + 40, y);
	ResumeBtn.setPos(x+80, y);
	NextBtn.setPos(x + 120, y);
	PrevBtn.setPos(x + 160, y);

	Intro.setPos(x, y-65);
	CurrentSong.setPos(x, y-35);
	GetFiles files;
	BMusicName = files.getFiles("Data/Music/menu/");

	for (int i=0;i<BMusicName.size();i++)
		BMusic.push_back(Music(BMusicName.at(i)));

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
}

void Menu_Music::render()
{
	Intro.render();
	CurrentSong.render();

	NextBtn.render();
	PrevBtn.render();
	StopBtn.render();
	PauseBtn.render();
	ResumeBtn.render();


	drawRect(MusicBox);

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
