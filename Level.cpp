#include "common.h"

#include "Level.hpp"

Level::Level()
{
    // Initializes the "map" array
    for (int x = 0; x < 14; x++)
        for (int y = 0; y < 22; y++)
            a[x][y] = 0;

    
}

Level::~Level()
{
    free();
}

void Level::free()
{
    

    // Frees level datas
    for (int x = 0; x < 14; x++)
        for (int y = 0; y < 22; y++)
            a[x][y] = 0;
}        

void Level::readLevelData(std::string path)
{
    std::ifstream inp;
    inp.open(path.c_str());
    for (int x = 0; x < 14; x++)
        for (int y = 0; y < 22; y++)
            inp >> a[x][y];
    inp.close();
}

void Level::drawMap(SDL_Renderer *gRenderer)
{
    for (int x=0;x<14;x++)
        for (int y=0;y<22;y++)
            {
                SDL_Rect fillRect= {L_POS_Y+y*L_LENGTH,L_POS_X+x*L_LENGTH,L_LENGTH,L_LENGTH};
                if (a[x][y]==1)
                {
                    if ((x+y)%2)
                    {
                        SDL_SetRenderDrawColor(gRenderer, 248, 247, 255, 255);
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(gRenderer, 224, 218, 255, 255);
                    }
                    
                }
                else if (a[x][y]==0)
                {
                    SDL_SetRenderDrawColor(gRenderer, 170, 165, 255, 255);
                }
                else 
                {
                    SDL_SetRenderDrawColor(gRenderer, 162, 239, 157, 255);
                }
                SDL_RenderFillRect( gRenderer, &fillRect );
            }

}


void Level::printArray()
{
    for (int i=0;i<14;i++){
        for (int j=0;j<22;j++)
            {
                std::cout << a[i][j] << " ";
            }
    std::cout << "\n";
    }
}
