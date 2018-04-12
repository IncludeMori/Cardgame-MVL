//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: basic game assets
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
	explicit DefaultTexture(int x, int y) : GameObj(x,y) {};
	DefaultTexture(const std::string &path, int x = 0, int y = 0);

	//Renders texture to screen at given point with various options 
	virtual void render(SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void setColor(Uint8 red, Uint8 green, Uint8 blue); //changes color
    void setBlendMode(SDL_BlendMode blending); //changes blend mode
	void setAlpha(Uint8 alpha); //changes alpha
	
	int getX();
	int getY();

	bool isEmpty();

protected:

};