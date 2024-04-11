#pragma once

#include "Game.hpp"
#include "Player.hpp"
#include "Dot.hpp"
#include "Coin.hpp"
#include "HUD_Text.hpp"

class Game
{
public:
	// The number of level
	const int LEVEL_NUMBER = 13;

	// 
	Game(const SDL_Window* gWindow,const SDL_Renderer* gRenderer,const TTF_Font* gFont);

	~Game();

	void free();
	// Loads media
	bool loadMedia(int levelNum);
	// Run a specific level
	void run(int i);

	// To reset media
	void closeMedia();

	// To load victory screen
	bool loadVictoryScreen();

	// To render victory screen
	void renderVictoryScreen();

	// To handle cheat code. Return 1 if the "SKIP" cheat code is activated, 0 otherwise
	bool handleCheatCode(SDL_Event& e);
private:
	// Player
	Player player;

	// Level
	Level level;

	// Dots
	Dot* dots;
	int nDots;

	// Coins
	Coin* coins;
	int nCoin, curCoin, unsavedCoin;

	// Death count texture
	HUD_Text deathCount;
	int death;

	// Coin count texture
	HUD_Text coinCount;

	// Level count texture
	HUD_Text levelCount;

	// Timer texture
	HUD_Text timer;

	

	// The sound effect that will be played
	Mix_Chunk* bell;
	Mix_Chunk* smack;
	Mix_Chunk* ding;

	//Cheat code masks
	bool isS, isK, isI, isP, isNR;

	//
	SDL_Texture* vTexture;

	

	// The window we are rendering to
	SDL_Window* window;

	// The window renderer
	SDL_Renderer* renderer;



	// Used font
	TTF_Font* font;
};