#include "PortInfo.hpp"



PortInfo::PortInfo()
{
	mPort = 3794;
	mPortTexture.loadFromRenderedText(getPortAsString());
}


PortInfo::~PortInfo()
{
}

void PortInfo::setPort(int port)
{
	if (isValid(port))
	{
		mPort = port;
		mPortTexture.loadFromRenderedText(getPortAsString());
	}
}

int PortInfo::getPort()
{
	return mPort;
}

std::string PortInfo::getPortAsString()
{
	return std::to_string(mPort);
}

bool PortInfo::isValid(int port)
{
	if (port < 65535 && port > 0)
		return true;
	else
		return false;

	//check if port is already listening??
}