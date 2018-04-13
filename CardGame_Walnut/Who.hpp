#pragma once

namespace who
{
	enum class type : int {
		PLAYER,
		OPPONENT
	};
	constexpr auto PLAYER = type::PLAYER;
	constexpr auto OPPONENT = type::OPPONENT;
}