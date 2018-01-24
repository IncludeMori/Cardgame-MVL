#include "W_ipconfig.hpp"

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <algorithm>

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

	for (int i = 0; i < mLocal_IP_Info.size(); i++)
		if (mLocal_IP_Info.at(i).empty())
			mLocal_IP_Info.erase(mLocal_IP_Info.begin()+i);

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

	for (int i = 0; i < mIP_Info.size(); i++)
		if (mIP_Info.at(i).empty())
			mIP_Info.erase(mIP_Info.begin() + i);
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