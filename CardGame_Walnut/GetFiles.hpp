#pragma once

#include <string>
#include <vector>
#include <boost\filesystem.hpp>



namespace fs = boost::filesystem;
class GetFiles
{
public:
	std::vector<std::string> getFiles(const std::string &p);

	int getSize();

private:
	int mSize = 0;
};

