#pragma once

struct MovePath{
    //Start position
    int xS,yS;
    //Finish position
    int xF,yF;

    //Moving time
    int moveTime;

    //Initializes structure
    MovePath(int xS,int yS,int xF,int yF,int moveTime) : xF(xF), xS(xS), yF(yF), yS(yS), moveTime(moveTime) {};

};