#pragma once

#include "Level.hpp"

class Level
{
public:

    //Initializes level's dimension
    static const int L_POS_X=0;
    static const int L_POS_Y=75;
    static const int L_WIDTH=880;
    static const int L_HEIGHT=560;

    //Initialize square's length
    static const int L_LENGTH=40;

    //Initializes level
    Level();

    //Deallocates level
    ~Level();

    //Deallocates memory
    void free();

    //Reads level data
    void readLevelData(std::string path);

    //Draws map
    void drawMap(SDL_Renderer* gRenderer);

    //Print array for debug purpose
    void printArray();

    //Gets map value in a specific pos
    int getMapValue(int y,int x);

    //Gets coordinate in the array based on its coordinate in the UI
    int getMapValue2(int y,int x);

    //Check if the upper block is the background
    bool uBackground(int y,int x);

    //Check if the lower block is the background
    bool dBackground(int y,int x);

    //Check if the left block is the background
    bool lBackground(int y,int x);

    //Check if the right block is the background
    bool rBackground(int y,int x);

    //To get the i'th checkpoint spawn X coordinate
    int getSpawnPointX(int i);

    //To get the i'th checkpoint spawn Y coordinate
    int getSpawnPointY(int i);

    //To get the number of checkpoints (including start and finish)
    int getCheckpointNum();

    //To load victory screen
    bool loadVictoryScreen(SDL_Renderer *gRenderer);

    //To render victory screen
    void renderVictoryScreen(SDL_Renderer *gRenderer);

    

private: 

    // The map that will be stored inside an array
    //  0 = Background, 1 = Floor tile, 2 = Start area, 3 = Finish area , 4+ = Checkpoint number #1+
    int a[14][22];

    //A vector that contains the checkpoint spawn position
    std::vector <int> spawnX;
    std::vector <int> spawnY;

    //The victory screen
    SDL_Texture *vTexture;

    //Death counter parameters
    SDL_Texture *dcTexture;
    int dcWidth,dcHeight;
    
    //Coin counter parameters
    SDL_Texture *ccTexture;
    int ccWidth,ccHeight;

    //Round counter parameters
    SDL_Texture *rcTexture;
    int rcWidth,rcHeight;


    //Timer parameters


    

};