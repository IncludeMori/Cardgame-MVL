//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: basic buttons
//
#pragma once

#include "DefaultTexture.hpp"

class Button : public DefaultTexture
{
public:
	Button();
	Button(int x, int y);
	~Button();

	void update();
	void disable();

	virtual bool IsPressed();

private:
	bool isEnabled;
};