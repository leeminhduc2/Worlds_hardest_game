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

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Player
Player player;

// Level
Level level;

//Dots
std::vector<Dot> dots;

//Coin

Coin coin= Coin(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

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
bool loadMedia()
{
	// Loading success flag
	bool success = 1;

	// Loads player
	if (!player.loadFile("Player.bmp", gRenderer))
	{
		std::cout << "Failed to load out player!\n";
		success = 0;
	}
	else{
	player.setBlendMode( SDL_BLENDMODE_BLEND );
	}

	//Loads coin
	
	if (!coin.loadFromFile("coin_sheet.png", gRenderer))
	{
		std::cout << "Failed to load out player!\n";
		success = 0;
	}
	else{
	coin.setBlendMode( SDL_BLENDMODE_BLEND );
	}

	{
		std::ifstream inp;
		inp.open("level1_dots.txt");
		int m;
		inp >> m;
		while (m--)
		{
			Dot dot;
			// Loads a dot
			if (!dot.loadImage("Dot.bmp", gRenderer))
			{
				std::cout << "Failed to load out dot!\n";
				success = 0;
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

	level.readLevelData("level1.txt");


	return success;
}
void close()
{
	// Remove loaded images
	player.free();

	// Remove level
	level.free();


	//Remove coin
	coin.free();

	// Remove dot
	for (auto dot : dots)
		dot.free();

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	if (!init())
	{
		std::cout << "Failed to initialize!\n";
		return -1;
	}
	if (!loadMedia())
	{
		std::cout << "Failed to load media!\n";
		return -1;
	}
	// Main loop flag
	bool quit = 0;

	// Event handler
	SDL_Event event;

	int frame=0;

	// While application is running
	while (!quit)
	{

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
			
			int i=0;
			for (Dot dot : dots)
			{
				if (player.checkCollision(currentTime, dot))
				{
					player.setPStatus(0);
					break;
				}
				++i;
			}
			// Move the dot
			player.move(level);
		}
		else
		{
			player.setAlpha(std::max(0,player.getAlphaValue()-3));
			if (player.getAlphaValue()==0)
			{
				player.setAlpha(255);
				player.setPosX(125);
				player.setPosY(360);
				player.setPStatus(1);
			}
			
		}

		

		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		
		// Render map (DO NOT PUT THIS LINE OF CODE BEHIND ANY OBJECT RENDER COMMAND, OR YOUR OBJECT WILL BE OVERLAPPED)
		level.drawMap(gRenderer);
		
		//Render coin
		coin.render(gRenderer,frame/4);
		++frame;
		if (frame/4==22) frame=0;


		

		// Render dot
		for (auto dot : dots)
			dot.render(currentTime, gRenderer);

		// Render player
		player.render(player.getPlayerPosX(), player.getPlayerPosY(), gRenderer);

		// Update screen
		SDL_RenderPresent(gRenderer);
	}

	// Free resources
	close();
}