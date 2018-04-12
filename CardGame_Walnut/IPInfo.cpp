#include "IPInfo.hpp"

#include <iostream>

IPInfo::IPInfo()
{
	int x = 0;
	size = 24;

	mChangePortBtn.loadFromFile("Data/changeport.png");
	
	if (mIpConfg.getIpInfo().size() > 0)
		mIPTexture[0].loadFromRenderedText("                 IPv4:    "+ mIpConfg.getIpInfo().at(0).substr(mIpConfg.getIpInfo().at(0).find_first_of(":") + 1, mIpConfg.getIpInfo().at(0).size()), size);
	else
		mIPTexture[0].loadFromRenderedText("Error: getIP() failed to connect", size);
	
	if (mIpConfg.getLocalIpInfo().size() > 0)
		mIPTexture[1].loadFromRenderedText("(Local)IPv4:    " + mIpConfg.getLocalIpInfo().at(0).substr(mIpConfg.getLocalIpInfo().at(0).find_first_of(":") + 1, mIpConfg.getLocalIpInfo().at(0).size()), size);
	else
		mIPTexture[1].loadFromRenderedText("Not able to get local IP. Please use cmd>ipconfig", size);


	mPort = 3794;
	mPortTexture.loadFromRenderedText("               Port:    " + getPortAsString(), size);
}


IPInfo::~IPInfo()
{
}

void IPInfo::update()
{
}

void IPInfo::render()
{
	for (int i = 0; i < 2; i++)
		mIPTexture[i].render();
	mPortTexture.render();
	mChangePortBtn.render();
}
void IPInfo::setPos(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		mIPTexture[i].setPos(x, y);
		y = y + 40;
	}
	mPortTexture.setPos(x, y);
	mChangePortBtn.setPos(x + mPortTexture.getWidth() + 10, y-mChangePortBtn.getHeight()/4);
	
}

void IPInfo::setPort(int port)
{
	if (isValid(port))
	{
		mPort = port;
		
		mPortTexture.loadFromRenderedText("               Port:    " + getPortAsString());
	}
}

std::string IPInfo::getPortAsString()
{
	return std::to_string(mPort);
}

bool IPInfo::isValid(int port)
{
	if (port < 65535 && port > 0)
		return true;
	else
		return false;

	//check if port is already listening??
}