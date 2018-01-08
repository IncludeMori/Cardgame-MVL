#pragma once

#include "GameObj.hpp"

class ShowGameObjInfo
{
public:
	ShowGameObjInfo();
	~ShowGameObjInfo();


	void printToConsole(GameObj &obj);
	void renderInfoWindow(GameObj &obj);
};

