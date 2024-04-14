#pragma once

#include "UI.hpp"
#include "HUD_Text.hpp"
#include "HUD_Texture.hpp"

//User Interface
class UI {
public:
	//Allocator
	UI(int _nTexture, int _nText);

	//Destructor
	~UI();

	//Deallocator
	void free();

	//To set the top-left coordinate of the ith texture
	void setTextureCoor(int x, int y, int i);

	//To set the top-left coordinate of the ith text
	void setTextCoor(int x, int y, int i);

	//To load the ith texture
	void loadTexture(std::string path, SDL_Renderer* gRenderer, int i);

	//To load the ith text
	void loadText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont, int i);

	//To render the ith texture
	void renderTexture(int i, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

	//To render the ith text
	void renderText(int i, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

	//To get the coordinates of the ith texture
	int getTextureX(int i);
	int getTextureY(int i);
	
	//To get the dimensions of the ith texture
	int getTextureWidth(int i);
	int getTextureHeight(int i);

	//To get the coordinates of the ith text
	int getTextX(int i);
	int getTextY(int i);

	//To get the dimensions of the ith text
	int getTextWidth(int i);
	int getTextHeight(int i);



private:
	HUD_Texture* textureList;
	int nTexture;

	HUD_Text* textList;
	int nText;
};