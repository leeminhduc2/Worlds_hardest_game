
#include "common.h"
#include "UI.hpp"
#include "HUD_Text.hpp"
#include "HUD_Texture.hpp"

UI::UI(int _nTexture, int _nText)
{
	nTexture = _nTexture;
	textureList = new HUD_Texture[nTexture];
	nText = _nText;
	textList = new HUD_Text[nText];
}
UI::~UI()
{
	free();
}
void UI::free()
{
	for (int i = 0; i < nTexture; i++)
	{
		textureList[i].free();
		
	}
	nTexture = 0;
	textureList = NULL;
	for (int i = 0; i < nText; i++)
	{
		textList[i].free();
		
	}
	nText = 0;
	textList = NULL;
	
}
//To set the top-left coordinate of the ith texture
void UI::setTextureCoor(int x, int y, int i)
{
	if (i >= nTexture)
	{
		std::cout << "Invalid setTextureCoor() input\n";
		return;
	}
	textureList[i].setX(x);
	textureList[i].setY(y);
}

//To set the top-left coordinate of the ith text
void UI::setTextCoor(int x, int y, int i)
{
	if (i >= nText)
	{
		std::cout << "Invalid setTextCoor() input\n";
		return;
	}
	textList[i].setX(x);
	textList[i].setY(y);
}

//To load the ith texture
void UI::loadTexture(std::string path, SDL_Renderer* gRenderer, int i)
{
	textureList[i].loadTexture(path, gRenderer);
}

//To load the ith text
void UI::loadText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont, int i)
{
	textList[i].loadText(textureText, textColor, gRenderer, gFont);
}

//To render the ith texture
void UI::renderTexture(int i, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	textureList[i].renderTexture(textureList[i].getX(), textureList[i].getY(), gRenderer, clip);
}

//To render the ith text
void UI::renderText(int i, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	textList[i].renderText(textList[i].getX(), textList[i].getY(), gRenderer, clip);
}
//To get the coordinates of the ith texture
int UI::getTextureX(int i)
{
	return textureList[i].getX();
}
int UI::getTextureY(int i)
{
	return textureList[i].getY();
}

//To get the dimensions of the ith texture
int UI::getTextureWidth(int i)
{
	return textureList[i].getWidth();
}
int UI::getTextureHeight(int i)
{
	return textureList[i].getHeight();
}

//To get the coordinates of the ith text
int UI::getTextX(int i)
{
	return textList[i].getX();
}
int UI::getTextY(int i)
{
	return textList[i].getY();
}

//To get the dimensions of the ith text
int UI::getTextWidth(int i)
{
	return textList[i].getWidth();
}
int UI::getTextHeight(int i)
{
	return textList[i].getHeight();
}