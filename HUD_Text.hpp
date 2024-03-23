#pragma once

#include "HUD_Text.hpp"

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

private:
    //HUD Texture
    SDL_Texture *HTTexture;
    
    //HUD dimensions
    int HTWidth,HTHeight;
    
};