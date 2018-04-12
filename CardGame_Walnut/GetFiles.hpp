#pragma once

#include <string>
#include <vector>

class GetFiles
{
public:
	GetFiles() = default;
	
	std::vector<std::string> getFiles(const std::string &p);

	int getSize();

private:
	int mSize = 0;
};

