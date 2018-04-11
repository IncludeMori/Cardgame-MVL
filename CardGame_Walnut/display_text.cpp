#include "display_text.hpp"


Text::Text(const std::string &text)
{
	// space x+15px, newLine y+25px
	mSpace = -10;
	mNewLine = 1;

	mPosX = 0;
	mPosY = 0;

	std::string path = "Data/Font/font02.png";
	mTexture.loadFromFile(path);

	mText = text;
	//creates the font
	buildFont();
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// Public functions 
void Text::setPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
}
void Text::initText(const std::string &text)
{
	mText = text;
}


void Text::renderText()
{
	renderText(mPosX, mPosY, mText);
}
void Text::renderText(const std::string &text)
{
	renderText(mPosX, mPosY, text);
}
void Text::renderText(int x, int y, const std::string &text)
{
	//If the font has been built
	
		//Temp offsets
		int curX = x, curY = y;

		int test = text.length();
		//Go through the text
		for (int i = 0; i < test; ++i)
		{
			//If the current character is a space
			if (text[i] == ' ')
			{
				//Move over
				curX += mSpace;
			}
			else
			{
				
				//Get the ASCII value of the character
				int letter = (unsigned char)text[i];
				
				//Show the character
				mTexture.setPos(curX, curY);
				mTexture.render(&mChar[letter]);

				//Move over the width of the character with one pixel of padding
				curX += mChar[letter].w -5;
			}
		}
}

std::string Text::asString()
{
	return mText;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// Private functions 


void Text::buildFont()
{
	int x = 0;
	int y = 0;

	int xNumber = 0;
	int yNumber = 64;

	int w = 32;
	int h = 32;


	// A - Z
	for (int i = 0; i < 256; i++)
	{

		// !, . , ?
		if (i == 33)
		{
			mChar[i] = { 32,64,32,32 };
		}
		else if (i == 46)
		{
			mChar[i] = { 0,96,32,32 };
		}

		//numbers
		else if (i > 47 && i < 58)
		{
			
			mChar[i] = { xNumber,yNumber,w,h };
			xNumber = xNumber + 32;

		}



		else if (i == 63)
		{
			mChar[i] = { 64,64,32,32 };
		}
		// .............



		// if A-Z
		else if (i > 64 && i < 91)
		{
			// first row
			int g = 12 * 32;
			if (x > g)
			{
				y = y + 32;
				x = 0;
			}

			mChar[i] = { x,y,w,h };

			x = x + 32;


		} // A-Z

		
		else if (i > 96 && i < 123)
		{
	
			// first row
			int g = 12 * 32;
			if (x > g)
			{
				y = y + 32;
				x = 0;
			}
			mChar[i] = { x,y,w,h };

			x = x + 32;
		} // a-z
		else
		{
			mChar[i] = { 0,96,32,32 };
			x = 0;
			y = 0;
		}



		

	} // for


	
}// build font