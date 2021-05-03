#pragma once

#include <vector>

#include "BaseCard.hpp"
#include "DefaultTexture.hpp"

class Graveyard
{
public:
	Graveyard();
	Graveyard(int who);
	~Graveyard();

	void render();
	void add(std::shared_ptr<BaseCard> card);
	std::shared_ptr<BaseCard> get(int index);

	void show();
	bool ShowIsActive();

	void init(int who);
	void free();

protected:
	int mPosX, mPosY;
	int mCurrentSize;
	bool mIsActive;

	std::shared_ptr<BaseCard> mCards[50];
	DefaultTexture mEmptyGraveTexture;
};

