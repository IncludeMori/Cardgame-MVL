#pragma once
////////////////////////////////////////////////
//
// AUTHOR: MORITZ VOLKENANDT
// VERSION 0.01
// DATE: 06.27.2016
//
// Purpose: Handles the text input
//////////////////////////////////////////////
#include <string>

#include "DefaultTexture.hpp"

#include <iostream>
using namespace std;

class Text 
{
public:
	Text()
	{
		// space x+15px, newLine y+25px
		mSpace = -10;
		mNewLine = 1;

		mPosX = 0;
		mPosY = 0;

		std::string path = "Data/Font/font02.png";
		mTexture.loadFromFile(path);

		//creates the font
		buildFont();



	}
	Text(SDL_Texture *Texture); //one texture for all?
	Text(const std::string &text);
	~Text();

	//
	void initText(const std::string &text);
	void setPos(int x, int y);

	void renderText();
	void renderText(const std::string &text);
	void renderText(int x, int y, const std::string &text);

private:
	//functions
	void buildFont();

	// member variables
	// the font sprite sheet
	DefaultTexture mTexture;
	//the actual text
	std::string mText;

	int mPosX, mPosY;
	// ASCII 0-255
	SDL_Rect mChar[256];
	//
	int mSpace;
	int mNewLine;
};