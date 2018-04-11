#include "Name.hpp"

#include "gScreenSize.hpp"
#include "gRenderer.hpp"

Name::Name()
{
	CurrentValue = "Player_Unkown";
	loadFromRenderedText(CurrentValue);
	mBackground.loadFromFile("Data/Hero_Interface/name_background.png");
}


Name::~Name()
{
}

void Name::init(Who o,const std::string &name)
{
	//if (!name.empty())
	CurrentValue = name;
	loadFromRenderedText(CurrentValue);
	
	if (o == PLAYER)
	{
		setPos(700-10, SCREEN_HEIGHT - 163);
		mBackground.setPos(700-mBackground.getWidth()+mWidth+27, SCREEN_HEIGHT - 150 - mHeight/2-3);
	}
	else
	{
		setPos(700-10, 230);
		mBackground.setPos(700-mBackground.getWidth()+mWidth+27-12, 240-mHeight/2-3);
	}
}
void Name::setName(const std::string &name)
{

	CurrentValue = name;
	loadFromRenderedText(CurrentValue);
}

void Name::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	mBackground.render();
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX,mPosY, mWidth, mHeight };


	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(gRenderer, mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen

}