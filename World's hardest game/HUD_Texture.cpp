#include "common.h"
#include "HUD_Texture.hpp"

HUD_Texture::HUD_Texture()
{
	//Initialize
	HTTexture = NULL;
	HTWidth = HTHeight = 0;
	HTX = HTY = 0;
}

HUD_Texture::~HUD_Texture()
{
	//Deallocate
	free();
}

void HUD_Texture::free()
{
	if (HTTexture != NULL)
	{
		SDL_DestroyTexture(HTTexture);
		HTTexture = NULL;
		HTWidth = HTHeight = 0;
		HTX = HTY = 0;
	}
}


bool HUD_Texture::loadTexture(std::string path, SDL_Renderer* gRenderer)
{
	// Remove the existing texture
	free();

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << "with exitcode " << IMG_GetError() << "\n";
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture " << path.c_str() << "with exitcode " << SDL_GetError() << "\n";
		}
		else
		{
			// Get image dimensions
			HTWidth = loadedSurface->w;
			HTHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	HTTexture = newTexture;
	return HTTexture != NULL;

}


void HUD_Texture::renderTexture(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, HTWidth, HTHeight };
	//Render to screen
	SDL_RenderCopy(gRenderer, HTTexture, clip, &renderQuad);
}


int HUD_Texture::getWidth()
{
	return HTWidth;
}

int HUD_Texture::getHeight()
{
	return HTHeight;
}
int HUD_Texture::getX()
{
	return HTX;
}
int HUD_Texture::getY()
{
	return HTY;
}
void HUD_Texture::setX(int x)
{
	HTX = x;
}
void HUD_Texture::setY(int y)
{
	HTY = y;
}