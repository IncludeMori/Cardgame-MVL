#pragma once

#include "Effects.hpp"
#include "Card_Effects.hpp"

class ModifyStatsEffect : public Effects {


protected:
	int mAmount = 0;
	eTargetType mTarget = eTargetType::ERROR;
	eTargetTypeSpec mTargetSpec = eTargetTypeSpec::ERROR;
	eTargetStatType mStat = eTargetStatType::ERROR;

};