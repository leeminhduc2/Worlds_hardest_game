#pragma once

#include "Coin.hpp"

class Coin
{
public:
    static const int COIN_LENGTH = 20;
    static const int COIN_RAD = 10;

    // Initializes a coin with a specific pos
    Coin();

    // Deallocates memory
    ~Coin();

    // Load image at specified path
    bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

    // Deallocates the coin
    void free();

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(int alpha);

    // Render texture at initialized point
    void render(SDL_Renderer *gRenderer, int currentFrame);

    // Gets alpha value
    int getAlphaValue();

    //To get the X coordinate of the coin
    int getX();

    //To get the Y coordinate of the coin
    int getY();

    //To get the coin status
    int getStatus();

    //To set the coin status into value
    void setStatus(int value);

    //To set the X coordinate
    void setX(int x);

    //To set the Y coordinate
    void setY(int y);

private:
    // Coin upper left position
    int cPosX;
    int cPosY;

    // Coin hardware texture
    SDL_Texture* cTexture;

    // Current alpha value
    int cAlpha;

    // Coin status
    int cStatus;
};