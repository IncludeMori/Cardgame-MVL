#pragma once

#include "Card_Effects.hpp"

#include <string>

enum class StatIndex : int {

	Error = -1,
	Effect = 0,
	Type = 1,
	Target = 2,
	Target_Spec = 3,
	Stat = 4
};


class getEffectAsString
{
public:
	getEffectAsString();
	~getEffectAsString();

	std::string getAsString(StatIndex stat_index, int index);

};

