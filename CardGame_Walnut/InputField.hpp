#pragma once

#include <string>

#include "display_text.hpp"

class InputField
{
public:
	InputField();
	InputField(int width, int height);
	InputField(int x, int y, int w, int h);

	void update();
	void render();


private:
	Text mShowText;

	int mWidth, mHeight;
	DefaultTexture mBackground;
};

