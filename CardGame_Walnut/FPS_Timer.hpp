//
// @Author: Moritz Volkenandt (2017)
//
// Purpose: count frames per second
//
#pragma once

#include "Timer.hpp"
#include "display_text.hpp"

class Fps_Timer
{
public:
	Fps_Timer();

	void render();

	void start();
	void endFrame();

	float calcFps();

	void end();

private:
	const int MAX_FPS = 60;
	float mCurrentFps;
	int mCounted_frames;
	int TICKS_PER_FRAME = 1000 / MAX_FPS;

	Timer fpsTimer;
	Timer capTimer;

	Text ShowFps;
};