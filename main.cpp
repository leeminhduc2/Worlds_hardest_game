/* leeminhduc2 - 23020047 - UET-VNU */


#include "common.h"

//Includes internal libraries
#include "Player.hpp"
#include "Level.hpp"


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

//Level
Level level;

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
	level.readLevelData("level1.txt");
	return success;
	
}
void close()
{
	// Remove loaded images
	player.free();

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

		// Move the dot
		player.move();

		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render map
		level.drawMap(gRenderer);

		// Render objects
		player.render(player.getPlayerPosX(), player.getPlayerPosY(), gRenderer);


		// Update screen
		SDL_RenderPresent(gRenderer);
	}

	// Free resources
	close();
}