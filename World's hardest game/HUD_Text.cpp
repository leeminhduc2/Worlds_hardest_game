#include "common.h"
#include "HUD_Text.hpp"

HUD_Text::HUD_Text()
{
    //Initialize
    HTTexture=NULL;
    HTWidth = HTHeight = 0;
	HTX = HTY = 0;
}

HUD_Text::~HUD_Text()
{
    //Deallocate
    free();
}

void HUD_Text::free()
{
    if (HTTexture!=NULL)
    {
        SDL_DestroyTexture(HTTexture);
        HTTexture = NULL;
        HTWidth = HTHeight = 0;
		HTX = HTY = 0;
    }
}


bool HUD_Text::loadText(std::string textureText,SDL_Color textColor,SDL_Renderer *gRenderer,TTF_Font *gFont)
{
    //Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        HTTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( HTTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			HTWidth = textSurface->w;
			HTHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return HTTexture != NULL;

}

    
void HUD_Text::renderText(int x,int y,SDL_Renderer *gRenderer, SDL_Rect* clip)
{
    //Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, HTWidth, HTHeight };
	//Render to screen
	SDL_RenderCopy( gRenderer, HTTexture, clip, &renderQuad);
}


int HUD_Text::getWidth()
{
    return HTWidth;
}

int HUD_Text::getHeight()
{
    return HTHeight;
}
int HUD_Text::getX()
{
	return HTX;
}
int HUD_Text::getY()
{
	return HTY;
}

void HUD_Text::setX(int x)
{
	HTX = x;
}
void HUD_Text::setY(int y)
{
	HTY = y;
}