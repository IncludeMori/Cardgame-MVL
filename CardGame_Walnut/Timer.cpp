
#include "timer.hpp"

Timer::Timer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void Timer::start() 
{
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks(); // -> miliseconds since SDL init
	mPausedTicks = 0;
}

void Timer::stop() 
{
	mStarted = false;
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	// if timer is running and  not paused -> pause
	if (mStarted && !mPaused)
	{
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks; // paused ticks = ticks passed since the timer got initialized
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused -> unpause
	if (mStarted && mPaused)
	{
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;  

		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//timer time
	Uint32 time = 0;

	if (mStarted)
	{
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}

bool Timer::isStarted()
{
	return mStarted;
}

bool Timer::isPaused()
{
	return mPaused && mStarted;
}