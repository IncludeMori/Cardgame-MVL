#pragma once

#include <vector>
#include <string>

class DefaultAnimation
{
public:
	DefaultAnimation();
	DefaultAnimation(int amountOfFrames);
	DefaultAnimation(int amountOfFrames, const std::vector<std::string> &files);
	~DefaultAnimation();

	void update();
	void render();

	void loadTextures(const std::vector<std::string> &files);


private:
	int mAmountOfFrames;
	int mCurrentFrame;

};

