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
		case((int)eEffect::BATTLECRY):
			return "BATTLECRY";
			break;
		case((int)eEffect::DEATHWISH):
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
		case((int)eTarget::DECK):
			return "DECK";
			break;
		case((int)eTarget::FIELD):
			return "FIELD";
			break;
		case((int)eTarget::HAND):
			return "HAND";
			break;
		case((int)eTarget::SELF):
			return "SELF";
			break;
		}

		break;
	case(StatIndex::Target_Spec):

		switch (index)
		{
		case((int)eTarget_spec::ALL):
			return "ALL"; 
			break;
		case((int)eTarget_spec::RANDOM):
			return "RANDOM";
			break;
		case((int)eTarget_spec::TARGET):
			return "TARGET";
			break;
		}
		break;
	case(StatIndex::Stat):

		switch (index)
		{
		case((int)eStat::ATTACK):
			return "ATTACK";
			break;
		case((int)eStat::HEALTH):
			return "HEALTH";
			break;
		case((int)eStat::COST):
			return "COST";
			break;
		}
		break;
	}
}