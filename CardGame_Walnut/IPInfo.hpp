#pragma once

#include <memory>

#include "W_ipconfig.hpp"
#include "TTF_Text.hpp"

class IPInfo
{
public:
	IPInfo();
	~IPInfo();

	void render();

	void setPos(int x, int y);

private:
	W_ipconfig mIpConfg;

	TTF_Text mIPTexture[2];

	int size;
};

