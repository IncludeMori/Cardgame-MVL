#pragma once

#include <string>

#include "TTF_Text.hpp"
#include "Who.hpp"

class Name : public TTF_Text
{
public:
	Name();
	~Name();

	void init(Who o,const std::string &name);
	void setName(const std::string &name);

private:
};

