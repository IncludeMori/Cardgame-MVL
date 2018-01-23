#include "InputHandler.hpp"

#include <iostream>
#include <ctype.h>

InputHandler::InputHandler()
{
	mNewText = "";
	mLastScancode = -1;

}


InputHandler::~InputHandler()
{
}


void InputHandler::reset()
{
	mNewText = "";
}

bool InputHandler::update(SDL_Event &e)
{
	enum { SHIFT = 4097 };

	SDL_Keymod Keymod = SDL_GetModState();
	

	
	//e.key.keysym.mod
	if (e.key.type == SDL_KEYDOWN)
	{

		int Scancode = e.key.keysym.scancode;
		

		if (e.key.keysym.sym == SDLK_BACKSPACE && mNewText.length() > 0)
		{
			mNewText.pop_back();
		}

		if (Scancode == 55) //dot
			mNewText.push_back('.');

		if (Scancode >= 4 && Scancode <= 28 || Scancode >= 30 && Scancode <= 39) //gueltig
		{
			mLastKey = *SDL_GetKeyName(e.key.keysym.sym);
			if (Keymod != SHIFT)//->4097 = LShift apparently
				mLastKey = putchar(tolower(mLastKey));
			mNewText.push_back(mLastKey);
		}
		if (Scancode == 56)
		{
			if (mLastScancode == 225)
				mLastKey = '_';
			else
				mLastKey = '-';
			mNewText.push_back(mLastKey);
		}
		mLastScancode = Scancode;
	}

	
	//if user saved data
	return true;

	//else use is still writing 

	 return false;

}

std::string InputHandler::getMod()
{
	if (mNewText == mOldText)
	{
		mNewText = "";
		return mOldText;
	}
	return mNewText;
}
