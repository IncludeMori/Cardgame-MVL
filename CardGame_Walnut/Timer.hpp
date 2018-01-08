//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: eg fps calculation
//
#pragma once

#include <stdint.h>
#include <SDL.h>

// SDL based timer
class Timer
{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks(); //return passed time

	//status
	bool isStarted();
	bool isPaused();

private:
	//clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//status
	bool mPaused;
	bool mStarted;
};