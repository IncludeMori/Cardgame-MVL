#include "StatsSign.hpp"


StatsSign::StatsSign()
{

}
StatsSign::StatsSign(Stats_Size size, std::shared_ptr<SDL_Texture> texture, int width, int height)
{
	if (size == Stats_Size::STANDARD)
	{

		setTexture(texture);
		mWidth = width;
		mHeight = height;

		int x = 0, y = 0, w = 35, h = 35;
		for (int i = 1; i < 9; i++)
		{
			mNumbers[i] = { x,y,w,h };
			x += 35;

			if (i == 5) { x = 0; y += 35; }
		}
		mNumbers[0] = { x + 35,y,w,h };
		mNumbers[10] = { 0,y + 35,w,h };
		mNumbers[11] = { 35,70,35,35 };

		mPosX = 0;
		mPosY = 0;
		mWidth = 35;
		mHeight = 35;

		mCurrentValue = 0;
		mBaseValue = 0;
	}
	else //hover
	{
		mTexture = nullptr;
		loadFromFile("Data/BigCard_Interface/numbers_big.png");

		int x = 0, y = 0, w = 50, h = 50;
		for (int i = 1; i < 9; i++)
		{
			mNumbers[i] = { x,y,w,h };
			x += 50;

			if (i == 5) { x = 0; y += 50; }
		}
		mNumbers[0] = { x + 50,y,w,h };
		mNumbers[10] = { 0,y + 50,w,h };
		mNumbers[11] = { 50,100,50,50 };

		mPosX = 0;
		mPosY = 0;
		mWidth = 50;
		mHeight = 50;

		mCurrentValue = 0;
		mBaseValue = 0;
	}
}

void StatsSign::move(int x, int y)
{
	mPosX += x;
	mPosY += y;
}


