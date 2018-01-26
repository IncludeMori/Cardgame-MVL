#pragma once

#include <vector>
#include <string>
#include <memory>

#include "DefaultTexture.hpp"

class DefaultAnimation
{
public:
	DefaultAnimation();
	DefaultAnimation(const std::vector<std::string> &files);
	~DefaultAnimation();

	void update();
	void render();

	void loadTextures(const std::vector<std::string> &files);

	void setPos(int x, int y);


private:
	int mAmountOfFrames;
	int mCurrentFrame;

	std::vector<std::unique_ptr<DefaultTexture>> mTextures;

};

