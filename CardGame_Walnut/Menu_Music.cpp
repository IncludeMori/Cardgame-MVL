#include "Menu_Music.hpp"

#include <stdlib.h>
#include <time.h>

#include "GetFiles.hpp"

Menu_Music::Menu_Music()
{
	CurrentSong.setPos(10, 10);
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
	CurrentSong.render();

}


void Menu_Music::start()
{
	srand(time(nullptr));
	int i = rand() % BMusic.size();
	BMusic.at(i).start();

	CurrentSong.loadFromRenderedText(BMusicName.at(i));
	CurrentSongIndex = i;



}
