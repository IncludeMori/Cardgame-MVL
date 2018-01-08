//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: audio
//
// In zwei Dateien aufteilen??
#pragma once

// SDL-libs
#include <SDL_mixer.h>

#include <string>

// Sound effects
class Sample
{
public:
	Sample();
	~Sample();

	bool loadChunkFromFile(std::string path); //load effect from file

	//various actions
	void start(int channel); 
	void pause(int channel); 
	void stop(); 
		 
	void free(); //close

private:
	Mix_Chunk* mChunk; // the effect file
};

//Background music
class Music
{
public:
	Music();
	~Music();
	
	bool loadMusicFromFile(std::string path); //load music from file

	//various actions									  
	void start();   
	void pause();    
	void stop();     
					 
	void free(); //close

private:
	Mix_Music* mMusic; // The music file
};