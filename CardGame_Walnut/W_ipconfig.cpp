#include "W_ipconfig.hpp"

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <algorithm>
/*
W_ipconfig::W_ipconfig()
{
	system("ipconfig > ipconfig.txt");
	system("nslookup myip.opendns.com. resolver1.opendns.com > ipnet.txt");

	//LOCAL
	std::ifstream ipconfigFile("ipconfig.txt");
	mLocal_IP_Info.push_back("");

	while (std::getline(ipconfigFile, mLocal_IP_Info.at(mLocal_IP_Info.size()-1)))
	{
		//remove spaces
		mLocal_IP_Info.at(mLocal_IP_Info.size()-1).erase(std::remove_if(mLocal_IP_Info.at(mLocal_IP_Info.size() - 1).begin(), mLocal_IP_Info.at(mLocal_IP_Info.size() - 1).end(), isspace), mLocal_IP_Info.at(mLocal_IP_Info.size() - 1).end());


		if (mLocal_IP_Info.at(mLocal_IP_Info.size() - 1).substr(0, 4) == "IPv4")
			std::cout << mLocal_IP_Info.at(mLocal_IP_Info.size() - 1) << std::endl;
		//std::cout << test << std::endl;
		mLocal_IP_Info.push_back("");
	}

	std::vector<std::string>::iterator iter2;
	for (iter2 = mLocal_IP_Info.begin(); iter2 != mLocal_IP_Info.end();)
	{
		if (iter2->empty())
		{
			iter2 = mLocal_IP_Info.erase(iter2);
		}
		else if (iter2->substr(0, 4) != "IPv4")
			iter2 = mLocal_IP_Info.erase(iter2);
		else
			++iter2;
	}

	//NET
	std::ifstream ipNetFile("ipnet.txt");
	mIP_Info.push_back("");

	while (std::getline(ipNetFile, mIP_Info.at(mIP_Info.size() - 1)))
	{
		//remove spaces
		mIP_Info.at(mIP_Info.size() - 1).erase(std::remove_if(mIP_Info.at(mIP_Info.size() - 1).begin(), mIP_Info.at(mIP_Info.size() - 1).end(), isspace), mIP_Info.at(mIP_Info.size() - 1).end());


		if (mIP_Info.at(mIP_Info.size() - 1).substr(0, 4) == "Address")
			std::cout << mIP_Info.at(mIP_Info.size() - 1) << std::endl;
		//std::cout << test << std::endl;
		mIP_Info.push_back("");
	}

	std::vector<std::string>::iterator iter;
	for (iter = mIP_Info.begin(); iter != mIP_Info.end();)
	{
		if (iter->empty())
		{
			iter = mIP_Info.erase(iter);
		}
		else if (iter->substr(0, 4) != "Addr")
			iter = mIP_Info.erase(iter);
		else
			++iter;
	}

	mIP_Info.erase(mIP_Info.begin());
	//whats left
	for (auto i : mLocal_IP_Info)
		std::cout << "left:" << i << "-" << std::endl;
	for (auto i : mIP_Info)
		std::cout << "left:" << i << "-" << std::endl;

}


W_ipconfig::~W_ipconfig()
{
}

std::vector<std::string> W_ipconfig::getLocalIpInfo()
{
	return mLocal_IP_Info;
}

std::vector<std::string> W_ipconfig::getIpInfo()
{
	return mIP_Info;
}


*/