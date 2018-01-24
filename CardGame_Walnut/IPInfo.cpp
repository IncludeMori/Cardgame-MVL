#include "IPInfo.hpp"

#include <iostream>

IPInfo::IPInfo()
{
	int x = 0;
	int size = 16;
	
		mIPTexture[0].loadFromRenderedText(size, mIpConfg.getIpInfo().at(0).substr(mIpConfg.getIpInfo().at(0).find_first_of(":")+1, mIpConfg.getIpInfo().at(0).size()));
	
		mIPTexture[1].loadFromRenderedText(size,mIpConfg.getLocalIpInfo().at(0).substr(mIpConfg.getLocalIpInfo().at(0).find_first_of(":")+1, mIpConfg.getLocalIpInfo().at(0).size()));
	

}


IPInfo::~IPInfo()
{
}

void IPInfo::render()
{
	for (int i = 0; i < 27; i++)
		mIPTexture[i].render();
}
void IPInfo::setPos(int x, int y)
{
	for (int i = 0; i < 27; i++)
	{
		mIPTexture[i].setPos(x, y);
		y = y + 20;
	}
}
