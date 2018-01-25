#include "IPInfo.hpp"

#include <iostream>

IPInfo::IPInfo()
{
	int x = 0;
	size = 24;


	
	if (mIpConfg.getIpInfo().size() > 0)
		mIPTexture[0].loadFromRenderedText(size,"                 IPv4:    "+ mIpConfg.getIpInfo().at(0).substr(mIpConfg.getIpInfo().at(0).find_first_of(":") + 1, mIpConfg.getIpInfo().at(0).size()));
	else
		mIPTexture[0].loadFromRenderedText(size,"Error: getIP() failed to connect");
	
	if (mIpConfg.getLocalIpInfo().size() > 0)
		mIPTexture[1].loadFromRenderedText(size, "(Local)IPv4:    " + mIpConfg.getLocalIpInfo().at(0).substr(mIpConfg.getLocalIpInfo().at(0).find_first_of(":") + 1, mIpConfg.getLocalIpInfo().at(0).size()));
	else
		mIPTexture[1].loadFromRenderedText(size, "Not able to get local IP. Please use cmd>ipconfig");


	
}


IPInfo::~IPInfo()
{
}

void IPInfo::render()
{
	for (int i = 0; i < 2; i++)
		mIPTexture[i].render();
	
}
void IPInfo::setPos(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		mIPTexture[i].setPos(x, y);
		y = y + 40;
	}
	
}
