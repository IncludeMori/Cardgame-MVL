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

private:
	void start();

	void pause();
	void resume();

	void playNext();
	void mute();

	std::vector<Music> BMusic;
	std::vector<std::string> BMusicName;

	Button Next, Resume, Stop, Mute;
	TTF_Text CurrentSong;
	int CurrentSongIndex;

};

