#pragma once

#include "BaseCard.hpp"

class EffectCard : public BaseCard , public std::enable_shared_from_this<EffectCard>
{
public:
	EffectCard();
	EffectCard(std::string &path);

	void play(const std::shared_ptr<Field> &Field);

	void renderIcons();
	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(bool &hoverIsActive, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderCardback(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	bool mouseIsAbove();

	bool activateEffect();

	void moveSigns(int x, int y);
	void setPos(int x, int y); //mPosX = x; mPosY = y;

private:
};

