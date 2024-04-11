#pragma once

#include "HUD_Text.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <corecrt_math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class HUD_Text
{
public:
    //Initialize HUD
    HUD_Text();

    //Deallocate HUD
    ~HUD_Text();

    //Deallocate memory
    void free();

    //To load a specific text
    bool loadText(std::string textureText,SDL_Color textColor,SDL_Renderer *gRenderer,TTF_Font *gFont);

    //To render a specific text
    void renderText(int x,int y,SDL_Renderer *gRenderer, SDL_Rect* clip=NULL);

    //To get HUD Text Width
    int getWidth();

    //To get HUD Text Height
    int getHeight();

    //To get HUD Text top left positions
    int getX();
    int getY();

    //To set the HUD Text top left positions
    void setX(int x = 0);
    void setY(int y = 0);

private:
    //HUD Texture
    SDL_Texture* HTTexture;
    
    //HUD dimensions
    int HTWidth,HTHeight;

    //HUD top left position
    int HTX, HTY;
    
};