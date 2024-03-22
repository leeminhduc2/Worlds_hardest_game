/* leeminhduc2 - 23020047 - UET-VNU */

#include "common.h"

// Includes internal libraries
#include "Player.hpp"
#include "Level.hpp"
#include "Dot.hpp"
#include "Coin.hpp"

// The window we are rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// The number of level
const int LEVEL_NUMBER = 1;

//The victory screen
SDL_Texture *vTexture = NULL;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void closeGame();

// Run a specific level
void run(int i);

// To reset media
void closeMedia();

//To load victory screen
bool loadVictoryScreen();

//To render victory screen
void renderVictoryScreen();

// Player
Player player;

// Level
Level level;

// Dots
std::vector<Dot> dots;

// Coins
Coin* coins;
int nCoin,curCoin;
void renderVictoryScreen()
{
	// Set up rendering space and render to screen
	SDL_Rect renderRect = {0, 0, SCREEN_WIDTH, SCREEN_WIDTH};
	

	// Render to screen
	SDL_RenderCopy(gRenderer, vTexture, &renderRect, &renderRect);
}
bool loadVictoryScreen()
{
	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image
	SDL_Surface *loadedSurface = IMG_Load("Resources/Victory_Screen.jpg");
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << "Resources/Victory_Screen.jpg" << "with exitcode " << IMG_GetError();
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture " << "Resources/Victory_Screen.jpg" << "with exitcode " << SDL_GetError();
		}
		else
		{
			
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	vTexture = newTexture;
	return vTexture != NULL;
}
bool init()
{
	// Initialization flag
	bool success = 1;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL couldn't initialize with exitcode\n";
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!\n";
		}

		// Create window
		gWindow = SDL_CreateWindow("World's hardest game by leeminhduc2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created with exitcode\n";
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				std::cout << "Renderer could not be created\n";
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image couldn't initialize with exitocde\n";

					success = false;
				}
			}
		}
	}

	return success;
}
bool loadMedia(int levelNum)
{
	// Loading success flag
	bool success = 1;

	//Load victory screen
	if (!loadVictoryScreen())
	{
		std::cout << "Failed to load out Victory screen\n";
		return 0;
	}

	// Load level

	level.readLevelData("Resources/Level_datas/level" + std::to_string(levelNum) + ".txt");
	
	// Loads player
	if (!player.loadFile("Resources/Player.bmp", gRenderer))
	{
		std::cout << "Failed to load out player!\n";
		return 0;
	}
	else
	{
		
		player.setBlendMode(SDL_BLENDMODE_BLEND);
		
		player.setSpawnPoint(level.getSpawnPointX(0), level.getSpawnPointY(0));
		std::cerr << "OK";
		player.gotoSpawnPoint();
	}
	std::cerr << "OK";
	

	// Loads coins
	{
		std::ifstream inp;
		inp.open("Resources/Level_datas/level" + std::to_string(levelNum) + "_coins.txt");
		
		inp >> nCoin;
		coins = new Coin[nCoin];
		for (int i=0;i<nCoin;i++)
		{
			
			int x, y;
			inp >> x >> y;

			
			coins[i].setX(x);
			coins[i].setY(y);
			
			// Load a coin
			if (!coins[i].loadFromFile("Resources/coin_sheet.png", gRenderer))
			{
				std::cout << "Failed to load out coin!\n";
				return 0;
			}
			else
			{
				coins[i].setBlendMode(SDL_BLENDMODE_BLEND);
			}
			
			
		}
		inp.close();
		
	}
	
	// Load dots
	{
		std::ifstream inp;
		inp.open("Resources/Level_datas/level" + std::to_string(levelNum) + "_dots.txt");
		int m;
		inp >> m;
		while (m--)
		{
			Dot dot;
			// Loads a dot
			if (!dot.loadImage("Resources/Dot.bmp", gRenderer))
			{
				std::cout << "Failed to load out dot!\n";
				return 0;
			}

			int n;
			inp >> n;
			for (int i = 1; i <= n; i++)
			{

				int xF, xS, yF, yS, moveTime;
				inp >> xS >> yS >> xF >> yF >> moveTime;
				dot.addPath(xS, yS, xF, yF, moveTime);
			}
			dots.push_back(dot);
		}
		inp.close();
	}

	return success;
}
void closeMedia()
{
	// Close level
	level.free();

	// Close player entity
	player.free();

	// Close dots
	for (Dot dot : dots)
	{
		dot.free();
	}
	while ((int)dots.size())
		dots.pop_back();

	// Close coins
	coins = NULL;

	//Close victory screen image
	vTexture = NULL;
	
}
void closeGame()
{

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
void run(int levelNum)
{
	
	if (!loadMedia(levelNum))
	{
		std::cout << "Failed to load media for level " << levelNum << "!\n";
		closeMedia();
		return;
	}
	
	
	// Main loop flag
	bool quit = 0;

	// Check if the player has completed the level
	bool win=0;

	// Event handler
	SDL_Event event;

	int frame = 0;
	
	// While application is running
	while (!quit)
	{
		
		
		if (win==true)
		{
			
			// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		renderVictoryScreen();
		SDL_RenderPresent(gRenderer);
			SDL_Delay(3000);
			quit=true;
		}
		// Handle events on queue
		
		while (SDL_PollEvent(&event) != 0)
		{
			// User requests quit
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			// Handle input for the dot
			player.handleEvent(event);
		}
		int currentTime = SDL_GetTicks();
		if (player.getPlayerStatus())
		{
			
			int i = 0;
			for (Dot dot : dots)
			{
				if (player.checkCollision(currentTime, dot))
				{
					player.setPStatus(0);
					break;
				}
				++i;
			}
			if (player.getPlayerStatus()==0) continue;
			// If the player is not touch the dot, check if it touches any coin
			for (int i=0;i<nCoin;i++)
			{
				if (player.isTouchCoin(coins[i])&&coins[i].getStatus()==0)
					coins[i].setStatus(1);
			}
			// Move the dot
			player.move(level);
			//To check if the player touches any tile, including the start and finishes
			
			for (int i=2;i<2+level.getCheckpointNum();i++)
				if (player.isTouchTile(level,i))
					{
						
						player.setSpawnPoint(level.getSpawnPointX(i-2),level.getSpawnPointY(i-2));
						for (int j=0;j<nCoin;j++) 
						{
							if (coins[j].getStatus()==1)
							{
								coins[j].setStatus(2);
								++curCoin;
							}
						}
						if (i==3)
						{
							if (curCoin==nCoin) win=1;
						}
					}
			
		}
		else
		{
			player.setAlpha(std::max(0, player.getAlphaValue() - 3));
			if (player.getAlphaValue() == 0)
			{
				player.setAlpha(255);
				player.gotoSpawnPoint();
				player.setPStatus(1);
				for (int i=0;i<nCoin;i++)
					if (coins[i].getStatus() == 1)
					{
						coins[i].setStatus(0);
						coins[i].setAlpha(255);
					}
			}
		}
			for (int i=0;i<nCoin;i++)
			if (coins[i].getStatus() == 1)
			{
				coins[i].setAlpha(std::max(0, coins[i].getAlphaValue() - 3));
			}

		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render map (DO NOT PUT THIS LINE OF CODE BEHIND ANY OBJECT RENDER COMMAND, OR YOUR OBJECT WILL BE OVERLAPPED)
		level.drawMap(gRenderer);

		// Render coin
		for (int i=0;i<nCoin;i++)
			coins[i].render(gRenderer, frame / 4);
		++frame;
		if (frame / 4 == 22)
			frame = 0;

		// Render dot
		for (auto dot : dots)
			dot.render(currentTime, gRenderer);

		// Render player
		player.render(player.getPlayerPosX(), player.getPlayerPosY(), gRenderer);

		// Update screen
		SDL_RenderPresent(gRenderer);
	}
	closeMedia();
}
int main(int argc, char **argv)
{
	if (!init())
	{
		std::cout << "Failed to initialize!\n";
		return -1;
	}
	run(1);
	run(2);
	// Free resources
	std::cerr << "SUCCESS";
	closeGame();
}