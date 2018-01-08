#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "DefaultTexture.hpp"


class TTF_Text: public DefaultTexture
{
public:
	TTF_Text();
	TTF_Text(int size);
	TTF_Text(const std::string &text);

	~TTF_Text();

	bool loadFromRenderedText(int size,const std::string &textureText);
	bool loadFromRenderedText(const std::string &textureText);

	std::string AsString();
	

protected:
	std::string CurrentValue;
	int mSize = 28;
};

