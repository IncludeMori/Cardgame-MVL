

#include "Audio_class.hpp" // header


#include <iostream>

/////////////////////////////////////////////////////
//////// CLASS FOR SAMPLES-SOUND EFFECTS    /////////
/////////////////////////////////////////////////////
Sample::Sample()
{
	mChunk = NULL;

}

Sample::~Sample()
{
	free();

}

// Loads a audiofile // effects only
bool Sample::loadChunkFromFile(std::string path)
{
	mChunk = Mix_LoadWAV(path.c_str());	// can load wave, ogg,...sound effects

	return true;
}

void Sample::start(int channel) // Channel
{
	if (Mix_Paused(channel) == 1)
	{
		Mix_Resume(channel);
	}
	else
	{
		Mix_PlayChannel(channel, mChunk, 0);
	}
}

void Sample::pause(int channel)
{
	Mix_HaltChannel(channel);
}

void Sample::stop()
{
	// later if needed
}

//close
void Sample::free()
{
	Mix_FreeChunk(mChunk);
	mChunk = NULL;
}


//////////////////////////////////////////////////////
////////   CLASS FOR BACKGROUND-MUSIC   /////////////
/////////////////////////////////////////////////////

Music::Music()
{
	mMusic = NULL;
}
Music::Music(std::string &path)
{
	loadMusicFromFile(path);
}

Music::~Music()
{
	free();

}

bool Music::loadMusicFromFile(std::string &path)
{
	std::cout << "Load music from:" << path << std::endl;
	mMusic = Mix_LoadMUS(path.c_str()); // can load mp3,ogg,  etc (background music, only one at a time)
	if (mMusic == nullptr)
		std::cout << "EERRRROOOR" << std::endl;

	return true;
}

void Music::start()
{

	if (Mix_PausedMusic() == 1) // checks if the music is paused
	{
		Mix_ResumeMusic(); // if so, resume

		printf("Resume music");
	}
	else
	{
		Mix_PlayMusic(mMusic, -1); // otherwise start for the first time
		printf("StartMusic");
	}
}

void Music::pause()
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_PauseMusic();
	}

}

void Music::stop()
{
	Mix_HaltMusic();
}

//close
void Music::free()
{
	Mix_FreeMusic(mMusic);
	mMusic = NULL;
}
