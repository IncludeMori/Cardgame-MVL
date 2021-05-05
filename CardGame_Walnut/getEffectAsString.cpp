#include "getEffectAsString.hpp"



getEffectAsString::getEffectAsString()
{
}


getEffectAsString::~getEffectAsString()
{
}


std::string getEffectAsString::getAsString(StatIndex stat_index, int index)
{
	switch (stat_index)
	{
	case(StatIndex::Error):
		return "NULL";
		break;
	case(StatIndex::Effect):

		switch (index)
		{
		case((int)eEffectType::BATTLECRY):
			return "BATTLECRY";
			break;
		case((int)eEffectType::DEATHWISH):
			return "DEATHWISH";
			break;
		}

		break;
	case(StatIndex::Type):

		switch (index)
		{
		case((int)eType::BOOST):
			return "BOOST";
			break;
		}
		break;
	case(StatIndex::Target):

		switch (index)
		{
		case((int)eTargetType::DECK):
			return "DECK";
			break;
		case((int)eTargetType::FIELD):
			return "FIELD";
			break;
		case((int)eTargetType::HAND):
			return "HAND";
			break;
		case((int)eTargetType::SELF):
			return "SELF";
			break;
		}

		break;
	case(StatIndex::Target_Spec):

		switch (index)
		{
		case((int)eTargetTypeSpec::ALL):
			return "ALL"; 
			break;
		case((int)eTargetTypeSpec::RANDOM):
			return "RANDOM";
			break;
		case((int)eTargetTypeSpec::TARGET):
			return "TARGET";
			break;
		}
		break;
	case(StatIndex::Stat):

		switch (index)
		{
		case((int)eTargetStatType::ATTACK):
			return "ATTACK";
			break;
		case((int)eTargetStatType::HEALTH):
			return "HEALTH";
			break;
		case((int)eTargetStatType::COST):
			return "COST";
			break;
		}
		break;
	}
	return "ERROR";
}