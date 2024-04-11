#pragma once

#include "Dot.hpp"
#include "MovePath.hpp"

class Dot
{
public:
    static const int C_RAD=10;
    //Initializes a dot
    Dot();

    //Deallocates a dot
    ~Dot();

    //Deallocates memory
    void free();

    //Adds moving pattern
    void addPath(double xS,double yS,double xF,double yF,int moveTime, bool isCircular,double rad);

    //Load images in specified path
    bool loadImage(std::string path,SDL_Renderer *gRenderer);

    //Show the dot on the screen
    void render(int currentTime, SDL_Renderer *gRenderer, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Returns total cycle time
    int getTotalTime();

    //Return moving path's parameters
    double getXS(int i);
    double getYS(int i);
    double getXF(int i);
    double getYF(int i);
    int getMoveTime(int i);
    bool getIsCircular(int i);
    double getRad(int i);
    int getPatternSize();
    

private:
    std::vector <MovePath> pattern;
    int totalTime;
    
    SDL_Texture *cTexture;


};