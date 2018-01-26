#include "DefaultAnimation.hpp"


DefaultAnimation::DefaultAnimation()
{
}

DefaultAnimation::DefaultAnimation(const std::vector<std::string>& files)
{
	mAmountOfFrames = files.size();
	for (auto i : files)
		mTextures.push_back(std::move(std::unique_ptr<DefaultTexture>(new DefaultTexture(i))));

}


DefaultAnimation::~DefaultAnimation()
{
}

void DefaultAnimation::update()
{
	static int frame;
	//update anim frame
	if( frame / 10 >= mAmountOfFrames ) 
	{
		frame = 0; 
	}
	frame++;
}

void DefaultAnimation::render()
{
	mTextures.at(mCurrentFrame)->render();
}

void DefaultAnimation::loadTextures(const std::vector<std::string>& files)
{
	mAmountOfFrames = files.size();
	for (auto i : files)
		mTextures.push_back(std::move(std::unique_ptr<DefaultTexture>(new DefaultTexture(i))));
}

void DefaultAnimation::setPos(int x, int y)
{
	for (auto &i : mTextures)
		i->setPos(x, y);
}