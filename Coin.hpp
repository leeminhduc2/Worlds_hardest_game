#pragma once

#include "Coin.hpp"

class Coin
{
public:
    static const int COIN_LENGTH = 20;

    // Initializes a coin with a specific pos
    Coin(int x, int y);

    // Deallocates memory
    ~Coin();

    // Load image at specified path
    bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

    // Deallocates the coin
    void free();

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Render texture at initialized point
    void render(SDL_Renderer *gRenderer, int currentFrame);

    // Gets alpha value
    int getAlphaValue();

private:
    // Coin upper left position
    int cPosX;
    int cPosY;

    // Coin hardware texture
    SDL_Texture *cTexture;

    // Clip vector
    std::vector<SDL_Rect> cClips;

    // Current alpha value
    Uint8 cAlpha;
};