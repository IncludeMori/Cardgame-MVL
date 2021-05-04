//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: 
//
#pragma once

#include <SDL_image.h>
#include <string>
#include <memory>

#include "SDL_Deleter.hpp"
#include "GameObj.hpp"


class DefaultTexture : public GameObj
{
public:
	DefaultTexture() = default;
	DefaultTexture(int x, int y) : GameObj(x,y) {};
	DefaultTexture(const std::string& path, int x = 0, int y = 0) : GameObj(x, y, path) {};

	virtual void render(SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) override;
};