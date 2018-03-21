#pragma once

#include "DefaultTexture.hpp"

class Field_HoverEffect : public DefaultTexture
{
public:
	Field_HoverEffect();
	~Field_HoverEffect();

	void set(bool v);

	void render();

private:
	bool mIsActive;
};

