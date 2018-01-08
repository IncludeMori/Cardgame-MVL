#include "FPS_Timer.hpp"

Fps_Timer::Fps_Timer()
{
	mCurrentFps = 0;
	mCounted_frames = 0;
	fpsTimer.start();
}

void Fps_Timer::start()
{
	capTimer.start();
}

void Fps_Timer::endFrame()
{
	// add one frame
	mCounted_frames++;
	//delay if fps > MAX_FPS
	int frameTicks = capTimer.getTicks();
	if (frameTicks < TICKS_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(TICKS_PER_FRAME - frameTicks);
	}
}

float Fps_Timer::calcFps()
{
	mCurrentFps = mCounted_frames / (fpsTimer.getTicks() / 1000.f);
	return mCurrentFps;
}


void Fps_Timer::end()
{
	fpsTimer.stop();
	capTimer.stop();
}