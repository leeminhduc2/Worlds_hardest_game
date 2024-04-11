#include "common.h"
#include "Coin.hpp"

Coin::Coin()
{
    cPosX = 0;
    cPosY = 0;
    cTexture=NULL;
    
    cAlpha=255;
    cStatus=0;
    
}

Coin::~Coin()
{
    free();
}
bool Coin::loadFromFile(std::string path, SDL_Renderer *gRenderer)
{
    // Remove the existing texture
    free();

    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "with exitcode " << IMG_GetError();
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            std::cout << "Unable to create texture " << path.c_str() << "with exitcode " << SDL_GetError();
        }
        

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    cTexture = newTexture;
    return cTexture != NULL;
}

void Coin::free()
{
    // Free texture if it exists
    if (cTexture != NULL)
    {
        SDL_DestroyTexture(cTexture);
        cTexture = NULL;
        cPosX = 0;
        cPosY = 0;
        
        cStatus=0;
        cAlpha=0;
    }
    
}

void Coin::setBlendMode(SDL_BlendMode blending)
{
    // Set blending function
	SDL_SetTextureBlendMode(cTexture, blending);
}


void Coin::setAlpha(int alpha)
{
    // Modulate texture alpha
	SDL_SetTextureAlphaMod(cTexture, alpha);
	cAlpha = alpha;
}


void Coin::render(SDL_Renderer *gRenderer, int currentFrame)
{
    // Set up rendering space and render to screen
	SDL_Rect renderRect = {cPosX, cPosY, COIN_LENGTH, COIN_LENGTH};
	SDL_Rect Clip = {currentFrame*COIN_LENGTH,0,COIN_LENGTH,COIN_LENGTH};
	// Render to screen
	SDL_RenderCopy(gRenderer, cTexture, &Clip, &renderRect);
}

int Coin::getAlphaValue()
{
    return cAlpha;
}

int Coin::getX()
{
    return cPosX;
}

int Coin::getY()
{
    return cPosY;
}

int Coin::getStatus()
{
    return cStatus;
}

void Coin::setStatus(int value)
{   
    cStatus = value;
}

void Coin::setX(int x)
{
    cPosX=x;
}

void Coin::setY(int y)
{
    cPosY=y;
}
