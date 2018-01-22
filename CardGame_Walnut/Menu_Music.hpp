#pragma once

#include <vector>
#include <string>

#include "Audio_class.hpp"
#include "Button.hpp"
#include "TTF_Text.hpp"

class Menu_Music
{
public:
	Menu_Music();
	~Menu_Music();

	void update();
	void render();

	void stop();

private:
	void start();

	void callButton(int btn);
	//void pause();
	//void resume();

	//void playNext();
	//void playPrev();
	//void stop();

	std::vector<Music> BMusic;
	std::vector<std::string> BMusicName;
	//std::vector<std::string> BMusicAuthor;

	Button MusicBtn[5];
	TTF_Text CurrentSong, Intro;
	int CurrentSongIndex;
	SDL_Rect MusicBox;

};

