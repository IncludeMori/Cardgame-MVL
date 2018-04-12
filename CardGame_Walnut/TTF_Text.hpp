#pragma once

#include <string>
#include <SDL_ttf.h>

#include "DefaultTexture.hpp"

class TTF_Text: public DefaultTexture
{
public:
	TTF_Text() = default;
	TTF_Text(const std::string &text) {
		loadFromRenderedText(text);
	};

	void loadFromRenderedText(const std::string &textureText, int size = -1);

	std::string AsString();
	
protected:
	std::string mText;
	int mSize = 28;
};

