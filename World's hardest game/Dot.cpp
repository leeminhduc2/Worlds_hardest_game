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

void Dot::addPath(double xS,double yS,double xF,double yF,int moveTime,bool isCircular,double rad)
{
    pattern.push_back(MovePath(xS,yS,xF,yF,moveTime,isCircular,rad));
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
	currentTime %= totalTime;
    int x,y;
    for (int i=0;i<(int) pattern.size();i++)
    {
        if (currentTime>pattern[i].moveTime)
        {
            currentTime-=pattern[i].moveTime;
        }
        else
        {   
			if (pattern[i].isCircular)
			{
				x = pattern[i].xS + (pattern[i].rad * cos(pattern[i].xF+ (pattern[i].yF-pattern[i].xF)*(double (currentTime))/pattern[i].moveTime/180*M_PI));
				y = pattern[i].yS + (pattern[i].rad * sin(pattern[i].xF+ (pattern[i].yF-pattern[i].xF)*(double(currentTime))/pattern[i].moveTime/180*M_PI));
			}
			else 
			{
				x = pattern[i].xS + (pattern[i].xF - pattern[i].xS) * currentTime / pattern[i].moveTime;
				y = pattern[i].yS + (pattern[i].yF - pattern[i].yS) * currentTime / pattern[i].moveTime;
			}
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

//Returns total cycle time
    int Dot::getTotalTime(){
		return totalTime;
	}

    //Return moving path's parameters
    double Dot::getXS(int i){
		return pattern[i].xS;
	}
    double Dot::getYS(int i)
	{
		return pattern[i].yS;
	}
    double Dot::getXF(int i)
	{
		return pattern[i].xF;
	}
    double Dot::getYF(int i){
		return pattern[i].yF;
	}
    int Dot::getMoveTime(int i)
	{
		return pattern[i].moveTime;
	}
	int Dot::getPatternSize()
	{
		return (int) pattern.size();
	}
	bool Dot::getIsCircular(int i)
	{
		return pattern[i].isCircular;
	}
	double Dot::getRad(int i)
	{
		return pattern[i].rad;
	}