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
	using DefaultTexture::DefaultTexture;

	void disable();

	virtual bool IsPressed();

private:
	bool isEnabled = true;
};