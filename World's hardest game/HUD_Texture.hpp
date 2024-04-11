#pragma once

#include "HUD_Texture.hpp"
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

class HUD_Texture
{
public:
    //Initialize HUD
    HUD_Texture();

    //Deallocate HUD
    ~HUD_Texture();

    //Deallocate memory
    void free();

    //To load a specific text
    bool loadTexture(std::string path, SDL_Renderer* gRenderer);

    //To render a specific text
    void renderTexture(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

    //To get HUD Texture Width
    int getWidth();

    //To get HUD Texture Height
    int getHeight();

    //To get HUD Texture top left positions
    int getX();
    int getY();

    //To set the HUD Texture top left positions
    void setX(int x = 0);
    void setY(int y = 0);

private:
    //HUD Texture
    SDL_Texture* HTTexture;

    //HUD dimensions
    int HTWidth, HTHeight;

    //HUD top left position
    int HTX, HTY;

};