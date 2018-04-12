//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: render card-> health, atk, cost
//
#pragma once

#include "HeroHealth.hpp"

enum class Stats_Size {
	STANDARD = 0,
	HOVER = 1
};

class StatsSign : public HeroHealth
{
public:
	StatsSign();
	StatsSign(Stats_Size size);

	void move(int x, int y);

private:
};