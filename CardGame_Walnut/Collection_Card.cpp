#include "Collection_Card.hpp"

#include "sol\sol.hpp"
#include "gMouse.hpp"

#include "Renderer.hpp"

using namespace sdl2_Renderer;

Collection_Card::Collection_Card(std::string &path)
{
	

	sol::state lua;
	lua.script_file("Cards_Lua/Data/card_effects.lua");
	lua.script_file("Cards_Lua/"+path + ".lua");

	mName = path;
	
	mTexturePath = lua[mName]["path"];

	
}

bool Collection_Card::loadTexture()
{
	loadFromFile("Data/small/sbasic_card.png");
	if (mTexture != nullptr) 
		return true;

	return false;
}

void Collection_Card::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen
}

bool Collection_Card::mouseIsAbove()
{
	int mouseX = gMouse.getX();
	int mouseY = gMouse.getY();
	if (mouseX > mPosX && mouseX < mPosX + mWidth && mouseY > mPosY && mouseY < mPosY + mHeight)
	{
		return true;
	}
	else { return false; }
}

void Collection_Card::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
}

std::string Collection_Card::getName()
{
	return mName;
}