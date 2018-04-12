#include "TTF_Text.hpp"

#include "Renderer.hpp"
using namespace sdl2_Renderer;

void TTF_Text::loadFromRenderedText(const std::string &textureText, int size)
{
	if (size > 0)
		this->mSize = size;
	TTF_Font *font = TTF_OpenFont("Data/Font/gtr.ttf", this->mSize);

	SDL_Color textColor = { 0,0,0 }; //add as parameter

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (!textSurface)
	{
		std::cout << "Unable to render text surface. Error msg:" << TTF_GetError() << std::endl;
	}
	else
	{
		//Create texture from surface pixels
		this->mTexture.reset((SDL_CreateTextureFromSurface(Renderer.get(), textSurface)));
		if (!this->mTexture)
		{
			std::cout << "Unable to create texture from rendered text. Error msg:" << SDL_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			this->mWidth = textSurface->w;
			this->mHeight = textSurface->h;
		}

		//Get rid of old surface & font
		SDL_FreeSurface(textSurface);
		TTF_CloseFont(font);
	}

	if (this->mTexture != nullptr)
		this->mText = textureText;
}

std::string TTF_Text::AsString()
{
	return mText;
}


