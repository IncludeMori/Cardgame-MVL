#pragma once

enum class eEffectType : int
{
	ERROR = -1,
	BATTLECRY = 0,
	DEATHWISH = 1
};

enum class eType: int {
	ERROR = -1,
	BOOST = 0
};

enum class eTargetType : int
{
	ERROR = -1,
	NO_TARGET = 0,
	SELF = 1,
	FIELD = 2,
	HAND = 3,
	DECK = 4
};

//if eTarget != self
enum class eTargetTypeSpec : int
{
	ERROR = -1,
	RANDOM = 0,
	ALL = 1,
	TARGET = 2
};
// eTarget != self

enum class eTargetStatType : int {
	ERROR = -1,
	ATTACK = 0,
	HEALTH = 1,
	COST = 2
};

//copy enum_class stat from other file here