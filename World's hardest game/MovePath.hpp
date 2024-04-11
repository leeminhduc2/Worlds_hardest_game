#pragma once

struct MovePath{
    //Start position
    double xS,yS;
    //Finish position
    double xF,yF;

    //Moving time
    int moveTime;
    bool isCircular;
    double rad;

    //Initializes structure
    MovePath(double xS, double yS, double xF, double yF, int moveTime, bool isCircular,double rad) : xF(xF), xS(xS), yF(yF), yS(yS), moveTime(moveTime), isCircular(isCircular), rad(rad) {};

};