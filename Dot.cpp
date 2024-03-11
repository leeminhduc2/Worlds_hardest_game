#include "common.h"
#include "Dot.hpp"
#include "MovePath.hpp"


Dot::Dot()
{
    totalTime=0;
}

Dot::~Dot()
{
    free();
}

void Dot::free()
{
    while ((int)  pattern.size()>0) pattern.pop_back();
    totalTime=0;
}

void Dot::addPath(int xS,int yS,int xF,int yF,int moveTime)
{
    pattern.push_back(MovePath(xS,yS,xF,yF,moveTime));
	totalTime+=moveTime;
}

bool Dot::loadImage(std::string path,SDL_Renderer *gRenderer)
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
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

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
void Dot::render(int currentTime, SDL_Renderer *gRenderer, SDL_Rect *clip , double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    // Finds the current coordinate of the dot
    currentTime%=totalTime;
    int x,y;
    for (int i=0;i<(int) pattern.size();i++)
    {
        if (currentTime>pattern[i].moveTime)
        {
            currentTime-=pattern[i].moveTime;
        }
        else
        {   
            x=pattern[i].xS+(pattern[i].xF-pattern[i].xS)*currentTime/pattern[i].moveTime;
            y=pattern[i].yS+(pattern[i].yF-pattern[i].yS)*currentTime/pattern[i].moveTime;
            break;
        }
    }
    // Set up rendering space and render to screen
	SDL_Rect renderRect = {x, y, C_RAD*2, C_RAD*2};
	if (clip != NULL)
	{
		renderRect.w = clip->w;
		renderRect.h = clip->h;
	}
	// Render to screen
	SDL_RenderCopyEx(gRenderer, cTexture, clip, &renderRect, angle, center, flip);
}
