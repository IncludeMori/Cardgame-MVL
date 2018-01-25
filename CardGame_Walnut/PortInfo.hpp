#pragma once


#include <string>

#include "display_text.hpp"


class PortInfo
{
public:
	PortInfo();
	~PortInfo();

	void setPort(int port);

	int getPort();
	std::string getPortAsString();
private:
	bool isValid(int port);

	int mPort;

	Text mPortTexture;
};

