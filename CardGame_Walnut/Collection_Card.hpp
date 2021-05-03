#pragma once

#include "MonsterCard.hpp"

class Collection_Card : public DefaultTexture
{
public:
	Collection_Card(std::string &path);

	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setPos(int x, int y); //mPosX = x; mPosY = y;

	bool mouseIsAbove();

	bool loadTexture();

	std::string getName();

private:
	std::string mName;
	std::string mTexturePath;

};