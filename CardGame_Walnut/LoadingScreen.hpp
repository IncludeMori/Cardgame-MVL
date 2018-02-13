#pragma once

#include <iostream>
#include <thread>

#include "DefaultTexture.hpp"


class LoadingScreen
{
public:
	LoadingScreen();

	void start() {
		mThread = std::thread(&LoadingScreen::render, this);
		std::cout << "Start: Loading Screen" << std::endl;
	}
	void end() {
		mIsActive = false;
		mThread.join();
		std::cout << "End: Loading Screen" << std::endl;
	}

private:
	void render(); //

	int mPercent;
	std::thread mThread;

	bool mIsActive = true;
	DefaultTexture mLoading;

};