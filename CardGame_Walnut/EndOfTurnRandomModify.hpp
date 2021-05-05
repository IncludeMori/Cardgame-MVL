#pragma once
/*
Moritz Volkenandt
2021
@MIT License

Usage: Trigger an effect at the end of the players turn which modifies health,atk or cost
*/

#include "ModifyStatsEffect.hpp"

class EndOfTurnRandomModify : public ModifyStatsEffect {
	EndOfTurnRandomModify() { mTargetSpec = eTargetTypeSpec::RANDOM; };
	bool activate(BaseCard* card) override;
	bool activate() override;
};