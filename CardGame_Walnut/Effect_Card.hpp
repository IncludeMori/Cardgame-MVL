#pragma once

#include "Basic_Card.hpp"



class Effect_Card : public Basic_Card , public std::enable_shared_from_this<Effect_Card>
{
public:
	Effect_Card();
	Effect_Card(std::string &path);

	void play(const std::shared_ptr<Field> &Field);

	void renderSigns();
	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(bool &hoverIsActive, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderBackside(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	bool MouseIsAbove();

	bool activateEffect();

	void moveSigns(int x, int y);
	void setPos(int x, int y); //mPosX = x; mPosY = y;

private:
};

