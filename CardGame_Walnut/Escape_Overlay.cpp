#include "Escape_Overlay.hpp"
#include "gScreenSize.hpp"

Escape_Overlay::Escape_Overlay()
{
	mIsActive = false;


	mYesBtn.loadFromFile("Data/yes_concede.png");
	mNoBtn.loadFromFile("Data/no_concede.png");

	mQuestion.loadFromFile("Data/esc_question.png");

	mYesBtn.setPos(SCREEN_WIDTH/2 - mYesBtn.getWidth()/2-35, SCREEN_HEIGHT/2 + 25);
	mNoBtn.setPos(SCREEN_WIDTH / 2 - mYesBtn.getWidth() / 2+35, SCREEN_HEIGHT / 2+25 );
	mQuestion.setPos(SCREEN_WIDTH / 2 - mQuestion.getWidth() / 2, SCREEN_HEIGHT / 2 - mQuestion.getHeight() / 2);
	mKeyUp = true;
}

bool Escape_Overlay::update()
{
	if (mIsActive)
	{
		if (mYesBtn.IsPressed())
			return true;
		else if (mNoBtn.IsPressed())
			mIsActive = false;
	}
	return false;
}

bool Escape_Overlay::update(SDL_Event &e)
{
	if (mKeyUp)
	{
		if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			if (e.key.type == SDL_KEYDOWN)
			{
				{
					if (mIsActive)
						mIsActive = false;
					else
						mIsActive = true;

					mKeyUp = false;
				}
			}
		}
	}
	if (e.key.type == SDL_KEYUP)
	{
	    mKeyUp = true;
	}


	if (mIsActive)
	{
		if (mYesBtn.IsPressed())
		{
			mIsActive = false;
			return true;
		}
		else if (mNoBtn.IsPressed())
			mIsActive = false;
	}
	return false;

}

void Escape_Overlay::render()
{
	if (mIsActive)
	{
		mQuestion.render();
		mYesBtn.render();
		mNoBtn.render();
	}
}

void Escape_Overlay::setActive()
{
	mIsActive = true;
}
void Escape_Overlay::setInactive()
{
	mIsActive = false;
}

bool Escape_Overlay::isActive()
{
	return mIsActive;
}