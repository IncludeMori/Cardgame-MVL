#pragma once

#include "Create_Deck.hpp"

struct fdeleter
{
	void operator()(Create_Deck* cr) const
	{
		cr->free();
		delete cr;
	}
};