#include "common.h"

#include "Level.hpp"

Level::Level()
{
    // Initializes the "map" array
    for (int y = 0; y < 14; y++)
        for (int x = 0; x < 22; x++)
            a[y][x] = 0;
}

Level::~Level()
{
    free();
}

void Level::free()
{

    // Frees level datas
    for (int y = 0; y < 14; y++)
        for (int x = 0; x < 22; x++)
            a[y][x] = 0;
}

void Level::readLevelData(std::string path)
{
    std::ifstream inp;
    inp.open(path.c_str());
    for (int y = 0; y < 14; y++)
        for (int x = 0; x < 22; x++)
            inp >> a[y][x];
    inp.close();
}

void Level::drawMap(SDL_Renderer *gRenderer)
{
    // Draws the main playground
    for (int y = 0; y < 14; y++)
        for (int x = 0; x < 22; x++)
        {
            SDL_Rect fillRect = {L_POS_X + x * L_LENGTH, L_POS_Y + y * L_LENGTH, L_LENGTH, L_LENGTH};
            if (a[y][x] == 1)
            {
                if ((x + y) % 2)
                {
                    SDL_SetRenderDrawColor(gRenderer, 248, 247, 255, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(gRenderer, 224, 218, 255, 255);
                }
            }
            else if (a[y][x] == 0)
            {
                SDL_SetRenderDrawColor(gRenderer, 170, 165, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 162, 239, 157, 255);
            }
            SDL_RenderFillRect(gRenderer, &fillRect);

            
        }
    // Draws the black playground outline 
    SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
    for (int y = 0; y < 14; y++)
        for (int x = 0; x < 22; x++)
        if (a[y][x]!=0)
        {
            //Outline length
            const int DRAWER_LENGTH = 4;
            int coorY=L_POS_Y + y * L_LENGTH, coorX=L_POS_X + x * L_LENGTH;
            
            /*

            */
            if (uBackground(y,x))
            {
                SDL_Rect fillRect = {coorX, coorY-DRAWER_LENGTH, L_LENGTH, DRAWER_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            if (dBackground(y,x))
            {
                SDL_Rect fillRect = {coorX, coorY+L_LENGTH, L_LENGTH, DRAWER_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            if (lBackground(y,x))
            {
                SDL_Rect fillRect = {coorX-DRAWER_LENGTH, coorY, DRAWER_LENGTH, L_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            if (rBackground(y,x))
            {
                SDL_Rect fillRect = {coorX+L_LENGTH, coorY, DRAWER_LENGTH, L_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            if (uBackground(y,x)&&lBackground(y,x))
            {
                SDL_Rect fillRect = {coorX-DRAWER_LENGTH, coorY-DRAWER_LENGTH, DRAWER_LENGTH, DRAWER_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            if (uBackground(y,x)&&rBackground(y,x))
            {
                SDL_Rect fillRect = {coorX+L_LENGTH, coorY-DRAWER_LENGTH, DRAWER_LENGTH, DRAWER_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            if (dBackground(y,x)&&lBackground(y,x))
            {
                SDL_Rect fillRect = {coorX-DRAWER_LENGTH, coorY+L_LENGTH, DRAWER_LENGTH, DRAWER_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            if (dBackground(y,x)&&rBackground(y,x))
            {
                SDL_Rect fillRect = {coorX+L_LENGTH, coorY+L_LENGTH, DRAWER_LENGTH, DRAWER_LENGTH};
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
            
        }

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_Rect fillRect = {0, 0, SCREEN_WIDTH, L_POS_Y};
    SDL_RenderFillRect(gRenderer, &fillRect);
    fillRect = {0, SCREEN_HEIGHT - L_POS_Y, SCREEN_WIDTH, L_POS_Y};
    SDL_RenderFillRect(gRenderer, &fillRect);
}

void Level::printArray()
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int Level::getMapValue(int y, int x)
{
    return a[y][x];
}

int Level::getMapValue2(int y, int x)
{
    return a[(y - L_POS_Y) / L_LENGTH][x / L_LENGTH];
}

bool Level::uBackground(int y, int x)
{
    return (y > 0 && (!a[y - 1][x]));
}

bool Level::dBackground(int y, int x)
{
    return (y < 14 && (!a[y + 1][x]));
}

bool Level::lBackground(int y, int x)
{
    return (x > 0 && (!a[y][x - 1]));
}

bool Level::rBackground(int y, int x)
{
    return (x < 22 && (!a[y][x + 1]));
}
