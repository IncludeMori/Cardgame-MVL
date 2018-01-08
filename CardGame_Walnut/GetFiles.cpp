#include "GetFiles.hpp"

#include <boost/filesystem.hpp>
#include <iostream>
#include <algorithm>

namespace fs = boost::filesystem;

std::vector<std::string> GetFiles::getFiles(const std::string &p)
{
	fs::path path(p);
	std::vector<std::string> files;

	if (fs::exists(path))
	{
		if (fs::is_directory(path))
		{
			std::cout << "Path||Directory: " << path << std::endl;
			std::cout << "Files: " << std::endl;

			for (fs::directory_entry& x : fs::directory_iterator(path))
			{
				if (fs::is_regular_file(x))
				{
					files.push_back(x.path().filename().string());
					mSize++;
				}
			}

			std::sort(files.begin(), files.end());
			for (int i = 0; i < files.size(); i++)
				std::cout << files[i] << std::endl;

			return files;
		}
	}
	else return files;
}

int GetFiles::getSize()
{
	return mSize;
}