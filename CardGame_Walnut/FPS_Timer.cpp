#include "FPS_Timer.hpp"


Fps_Timer::Fps_Timer()
{
	ShowFps.setPos(5, 5);

	mCurrentFps = 0;
	mCounted_frames = 0;
	
}

void Fps_Timer::start()
{
	fpsTimer.start();
}

void Fps_Timer::render()
{
	ShowFps.renderText();
}
void Fps_Timer::startFrame()
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

	if (mCurrentFps > 59)
		mCurrentFps = 60;
	ShowFps.initText(std::to_string((int)mCurrentFps));
	return mCurrentFps;
}


void Fps_Timer::end()
{
	fpsTimer.stop();
	capTimer.stop();
}