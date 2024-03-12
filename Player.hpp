
#pragma once


#include "Level.hpp"
#include "Dot.hpp"
#include "Player.hpp"

class Player
{
public:
	static const int PLAYER_WIDTH = 30;
	static const int PLAYER_HEIGHT = 30;

	static const int PLAYER_VEL = 1;


	// Initializes the variables
	Player();

	// Deallocates memory
	~Player();

	// Deallocates texture
	void free();

	// Loads image at specified path
	bool loadFile(std::string path, SDL_Renderer *gRenderer);

	// Renders texture at (x,y)
	void render(int x, int y, SDL_Renderer *gRenderer, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets player's dimension
	int getPlayerWidth();
	int getPlayerHeight();

	// Gets player's position
	int getPlayerPosX();
	int getPlayerPosY();

	// Adjusts the player's velocity based on keys pressed
	void handleEvent(SDL_Event &e);

	// Player movement
	void move(Level level);

	// Set player status
	void setPStatus(bool currentStatus);

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );

	// See if player touches a dot
	bool checkCollision(int currentTime, Dot dot);

	//Returns the current alpha value
	int getAlphaValue();

	//Returns the player current status
	bool getPlayerStatus();

	//Set player X position
	void setPosX(int val);

	//Set player Y position
	void setPosY(int val);

	

private:
	// The position of the red block
	int pPosX, pPosY;

	// The "player" dimension
	int pWidth, pHeight;

	// The velocity of the red block
	int pVelX, pVelY;

	// The actual hardware texture
	SDL_Texture *pTexture;

	// Player status
	bool pStatus;

	// current Alpha value

	int pAlphaValue;
};