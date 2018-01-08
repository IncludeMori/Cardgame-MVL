/*
*
* /file Camera.hpp
* /brief camera handling
*
*
*Copyright (c) 2016 Moritz Volkenandt
*
*/
#pragma once


#include <SDL.h>
#include "Player.hpp"



class Camera
{
public:
	Camera();
	Camera(int x, int y, int width, int height, int maxheight);
	~Camera();

	// changes the "standard" camera data, size + max X&Y
	void changeData(int x, int y,int width, int height, int maxheight);

	// center the camera over obj
	void moveLeft();
	void moveRight();

	// check if camera is still inside mLevelWidth + mLevelHeight
	void checkBounds(); 

	bool isInside(int x, int y, int width, int height);
	// return the current position
	int getPosX();
	int getPosY();

	//returns the Camera Rect // position + width/height
	SDL_Rect getCamera();

private:
	// current area
	SDL_Rect mCamera;

	int sX, sY;
	int mPosX, mPosY;
	int mWidth;
	int mHeight;

	int mMaxHeight;

};


