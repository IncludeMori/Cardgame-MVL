#include "IPInfo.hpp"

#include <iostream>

IPInfo::IPInfo()
{
	int x = 0;
	int size = 16;
	for (int i = 0; i < mIpConfg.getIpInfo().size(); i++)
	{
		mIPTexture[i].loadFromRenderedText(size,mIpConfg.getIpInfo().at(i));
		std::cout << "->" << i << std::endl;
		std::cout << mIPTexture[i].AsString() << std::endl;
		x = i;
	}

	for (int i = x; i < mIpConfg.getLocalIpInfo().size() + (x - 1); i++)
	{
		std::cout << "i-x=" << i - x << std::endl;
		std::cout << "size:" << mIpConfg.getLocalIpInfo().size() << std::endl;
		mIPTexture[i].loadFromRenderedText(size,mIpConfg.getLocalIpInfo().at(i - (x)));
		std::cout << "->" << i << std::endl;
		std::cout << mIPTexture[i].AsString() << std::endl;
	}

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
