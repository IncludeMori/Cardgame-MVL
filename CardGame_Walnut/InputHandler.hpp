#pragma once

#include <string>
#include <SDL.h>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void reset();
	bool update(SDL_Event &e);


	std::string getMod();

private:
	char mLastKey;
	int mLastScancode;

	std::string mNewText;
	std::string mOldText;
	SDL_Rect Input_Name, Input_Attack, Input_Health, Input_Cost;
};

