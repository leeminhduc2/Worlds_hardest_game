#pragma once


class Level
{
public:

    //Initializes level's dimension
    static const int L_POS_X=75;
    static const int L_POS_Y=0;
    static const int L_WIDTH=880;
    static const int L_HEIGHT=560;

    //Initialize square's length
    static const int L_LENGTH=40;

    //Initializes level
    Level();

    //Deallocates level
    ~Level();

    //Deallovates memory
    void free();

    //Reads level data
    void readLevelData(std::string path);

    //Draws map
    void drawMap(SDL_Renderer* gRenderer);

    //for debug purpose
    void printArray();

private: 

    // The map that will be stored inside an array
    //  0 = Background, 1 = Floor tile, 2 = Start area, 3 = Finish area , 4+ = Checkpoint number #1+
    int a[14][22];


    

};