#include "Name.hpp"

#include "gScreenSize.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

Name::Name()
{
	mText = "Player_Unkown";
	loadFromRenderedText(mText);
	mBackground.loadFromFile("Data/Hero_Interface/name_background.png");
}


Name::~Name()
{
}

void Name::init(who::type o,const std::string &name)
{
	//if (!name.empty())
	mText = name;
	loadFromRenderedText(mText);
	
	if (o == who::type::PLAYER)
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

	mText = name;
	loadFromRenderedText(mText);
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


	SDL_RenderCopyEx(Renderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip); // renders texture to screen

}