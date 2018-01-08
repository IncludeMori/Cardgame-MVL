/*
*
* /file Camera.cpp
* /brief camera handling
*
*
*Copyright (c) 2016 Moritz Volkenandt
*
*/
#include "Camera.hpp"


Camera::Camera()
{
	mWidth = 0;
	mHeight = 0;
	mPosX = 0;
	mPosY = 0;
	mCamera = { 0,0,0,0 };


}

Camera::Camera(int x, int y, int width, int height, int maxheight)
{
	mWidth = width;
	mHeight = height;
	mPosX = x;
	mPosY = y;
	sX = x;
	sY = y;

	
	mCamera = { x,y,mWidth,mHeight };
	mCamera.w = mWidth;
	mCamera.h = mHeight;
	std::cout << x << "," << y << "," << mWidth << "," << mHeight << "," << std::endl;


}

Camera::~Camera()
{


} // ~LCamera

void Camera::changeData(int x, int y, int width, int height, int maxheight)
{
	mWidth = width;
	mHeight = height;

	std::cout << "Cam Widht/Height:" << mWidth << "|" << mHeight << std::endl;

	mPosX = x;
	mPosY = y;

	mMaxHeight = maxheight;

	mCamera = { x, y, mWidth,mHeight };

}


void Camera::moveLeft()
{
	mCamera.x += 5;
	checkBounds();

	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);
	SDL_RenderDrawRect(gRenderer, &mCamera);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Camera::moveRight()
{
	mCamera.x -= 5;
	checkBounds();

	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);
	SDL_RenderDrawRect(gRenderer, &mCamera);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Camera::checkBounds()
{

	//Keep the camera in bounds
	if (mCamera.x < mPosX)
	{
		mCamera.x = mPosX;
	}
	else if (mCamera.y < mPosY)
	{
		mCamera.y = mPosY;
	}
	else if (mCamera.y > mMaxHeight - mCamera.h)
	{
		mCamera.y = mMaxHeight - mCamera.h;
	}
} // checkBounds


bool Camera::isInside(int x, int y, int width, int height)
{
	if (y > mCamera.y && y < mCamera.y + mCamera.h && x > mCamera.x && x < mCamera.x +mCamera.w)
	{
		return true;
	}
	else
	    return false;
}


int Camera::getPosX()
{
	return mCamera.x-sX;
}

int Camera::getPosY()
{
	return mCamera.y-sY;
}

SDL_Rect Camera::getCamera()
{
	return mCamera;
}