#pragma once

#include <vector>

#include "Basic_Card.hpp"
#include "DefaultTexture.hpp"

class Graveyard
{
public:
	Graveyard();
	Graveyard(int who);
	~Graveyard();

	void render();
	void add(std::shared_ptr<Basic_Card> card);
	std::shared_ptr<Basic_Card> get(int index);

	void show();
	bool ShowIsActive();

	void init(int who);
	void free();

protected:
	int mPosX, mPosY;
	int mCurrentSize;
	bool mIsActive;

	std::shared_ptr<Basic_Card> mCards[50];
	DefaultTexture mEmptyGraveTexture;
};

