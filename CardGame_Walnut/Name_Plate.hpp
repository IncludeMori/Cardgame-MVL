#pragma once

#include "DefaultTexture.hpp"
#include "TTF_Text.hpp"

class Name_Plate
{
public:
	Name_Plate();
	Name_Plate(std::string &name);
	~Name_Plate();

	void render();

	void setPos(int x, int y);
	void setName(std::string &name);

private:
	DefaultTexture mBackground;
	std::string mName;
	TTF_Text mTTFName;
};

