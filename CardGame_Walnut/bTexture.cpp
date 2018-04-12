#include "bTexture.hpp"


#include "Renderer.hpp"
using namespace sdl2_Renderer;


bTexture::bTexture()
{
	mTexture = nullptr;
	mPosX = 0;
	mPosY = 0;
	mHeight = 0;
	mWidth = 0;
}
bTexture::~bTexture()
{
	free();
}



bool bTexture::loadFromFile(std::string path)
{
	std::cout << "Loading: " << path << std::endl;

	//delete preexisting textures
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//neutral colorkey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer.get(), loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	std::cout << mTexture << std::endl;
	return mTexture != NULL;
}

void bTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	mPosX = x;
	mPosY = y;

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(Renderer.get(), mTexture, clip, &renderQuad, angle, center, flip); // renders texture to screen

}

void bTexture::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
		mPosX = 0;
		mPosY = 0;
	}
}