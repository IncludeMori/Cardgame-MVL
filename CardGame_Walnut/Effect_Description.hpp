#pragma once

#include "TTF_Text.hpp"
#include "DefaultTexture.hpp"

#include <vector>

class Effect_Description
{
public:
	Effect_Description();
	~Effect_Description();

	void render();

	void setPos(int x, int y);
	void setEffect(std::vector<std::string> &effects);

	void free();

private:
	std::vector<TTF_Text> mEffectDescr;

	DefaultTexture mBackground;
};

