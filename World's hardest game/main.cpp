/* leeminhduc2 - 23020047 - UET-VNU */

#include "common.h"

// Includes internal libraries
#include "Player.hpp"
#include "Level.hpp"
#include "Dot.hpp"
#include "Coin.hpp"
#include "HUD_Text.hpp"
#include "HUD_Texture.hpp"
#include "UI.hpp"

// The window we are rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

//
SDL_Texture *vTexture = NULL;

// The number of level
const int LEVEL_NUMBER = 13;

// Globally used font
TTF_Font *gFont = NULL;

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

// To load victory screen
bool loadVictoryScreen();

// To render victory screen
void renderVictoryScreen();

// To handle cheat code. Return 1 if the "SKIP" cheat code is activated, 0 otherwise
bool handleCheatCode(SDL_Event& e);

// To run main menu interface
void runMainMenu();

// To check if the mouse button is inside the texture/text
bool isMouseInside(int x, int y, int x1, int y1, int width, int height);

//To run tutorial menu interface
void runTutorialMenu();


// Player
Player player;

// Level
Level level;

// Dots
Dot *dots;
int nDots;

// Coins
Coin *coins;
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

// The music that will be played
Mix_Music *gMusic = NULL;

// The sound effect that will be played
Mix_Chunk *gBell = NULL;
Mix_Chunk *gSmack = NULL;
Mix_Chunk *gDing = NULL;





//Mode select menu interface
UI modeMenu(5, 0);

//Hardness select menu interface
UI hardnessMenu(5, 0);

//Victory menu interface
UI victoryMenu(2, 3);

//Level select menu
UI levelMenu(31, 0);

bool isMouseInside(int x, int y, int x1, int y1, int width, int height)
{
	return (x >= x1 && x < x1 + width && y >= y1 && y < y1 + height);
}

//Cheat code masks
bool isS,isK,isI,isP,isNR;

bool handleCheatCode(SDL_Event& e)
{
	
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// Adjust the velocity
		if (e.key.keysym.sym == SDLK_s && !isS)
			isS = 1;
		if (e.key.keysym.sym == SDLK_k && !isK)
			isK = 1;
		if (e.key.keysym.sym == SDLK_i && !isI)
			isI = 1;
		if (e.key.keysym.sym == SDLK_p && !isP)
			isP = 1;

	}
	// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// Adjust the velocity
		if (e.key.keysym.sym == SDLK_s && isS)
			isS = 0;
		if (e.key.keysym.sym == SDLK_k && isK)
			isK = 0;
		if (e.key.keysym.sym == SDLK_i && isI)
			isI = 0;
		if (e.key.keysym.sym == SDLK_p && isP)
			isP = 0;
	}

	if (isS && isK && isI && isP && !isNR)
	{
		isNR = 1;
		return 1;
	}
	if (isNR && !(isK | isS | isI | isP)) isNR = 0;
	return 0;
}
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
		std::cout << "Unable to load image "
				  << "Resources/Victory_Screen.jpg"
				  << "with exitcode " << IMG_GetError();
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture "
					  << "Resources/Victory_Screen.jpg"
					  << "with exitcode " << SDL_GetError();
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
	Mix_Init(MIX_INIT_OGG);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
				Mix_Init(MIX_INIT_OGG);
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
						success = false;
					}
				
				
					// Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						success = false;
					}
					else
					{
						// Open the font
						gFont = TTF_OpenFont("ChakraPetch-Bold.ttf", 26);
						if (gFont == NULL)
						{
							printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
							success = false;
						}
					}
				
			}
		}
	}
	//Load music
	gMusic = Mix_LoadMUS("Resources/Soundtracks/music.ogg");
	gBell = Mix_LoadWAV("Resources/Soundtracks/bell.wav");
	gDing = Mix_LoadWAV("Resources/Soundtracks/ding.wav");
	gSmack = Mix_LoadWAV("Resources/Soundtracks/smack.wav");
	return success;
}
bool loadMedia(int levelNum)
{
	// Loading success flag
	bool success = 1;

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
		player.gotoSpawnPoint();
	}

	// Loads coins
	{
		curCoin = unsavedCoin = 0;
		std::ifstream inp;
		inp.open("Resources/Level_datas/level" + std::to_string(levelNum) + "_coins.txt");

		inp >> nCoin;
		coins = new Coin[nCoin];
		for (int i = 0; i < nCoin; i++)
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
		nDots = m;
		dots = new Dot[nDots];
		while (m--)
		{

			// Loads a dot
			if (!dots[m].loadImage("Resources/Dot.bmp", gRenderer))
			{
				std::cout << "Failed to load out dot!\n";
				return 0;
			}

			int n;
			inp >> n;
			for (int i = 1; i <= n; i++)
			{

				double xF, xS, yF, yS, moveTime,rad;
				bool isCircular;
				inp >> xS >> yS >> xF >> yF >> moveTime >> isCircular >> rad;
				dots[m].addPath(xS, yS, xF, yF, moveTime,isCircular, rad);
			}
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
	dots = NULL;
	nDots = 0;

	// Close and reset coin parameters
	coins = NULL;
	nCoin = curCoin = unsavedCoin = 0;
}
void closeGame()
{

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	Mix_FreeChunk(gBell);
	Mix_FreeChunk(gSmack);
	Mix_FreeChunk(gDing);
	gBell = NULL;
	gSmack = NULL;
	gDing = NULL;
	Mix_CloseAudio();
	Mix_Quit();
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
	bool win = 0;

	// Event handler
	SDL_Event event;

	int frame = 0;
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
				exit(0);
			}

			// Handle input for the dot
			player.handleEvent(event);
			if (handleCheatCode(event))
			{
				win = 1;
				Mix_PlayChannel(-1, gBell, 0);
			}
		}

		int currentTime = SDL_GetTicks();
		if (player.getPlayerStatus())
		{

			for (int j = 0; j < nDots; j++)
			{
				if (player.checkCollision(currentTime, dots[j]))
				{
					Mix_PlayChannel(-1, gSmack, 0);
					player.setPStatus(0);
					++death;
					break;
				}
			}

			if (player.getPlayerStatus() == 0)
				continue;
			// If the player isn't touch the dot, check if it touches any coin
			for (int i = 0; i < nCoin; i++)
			{
				if (player.isTouchCoin(coins[i]) && coins[i].getStatus() == 0)
				{
					Mix_PlayChannel(-1, gDing, 0);
					coins[i].setStatus(1);
					++unsavedCoin;
				}
			}

			// Move the player
			player.move(level);
			// To check if the player touches any tile, including the start and finishes

			for (int i = 2; i < 2 + level.getCheckpointNum(); i++)
				if (player.isTouchTile(level, i))
				{

					player.setSpawnPoint(level.getSpawnPointX(i - 2), level.getSpawnPointY(i - 2));
					for (int j = 0; j < nCoin; j++)
					{
						if (coins[j].getStatus() == 1)
						{
							coins[j].setStatus(2);
							++curCoin;
						}
					}
					if (i == 3)
					{
						if (curCoin == nCoin) {
							win = 1;
							Mix_PlayChannel(-1, gBell, 0);
						}
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
				for (int i = 0; i < nCoin; i++)
					if (coins[i].getStatus() == 1)
					{
						coins[i].setStatus(0);
						coins[i].setAlpha(255);
						--unsavedCoin;
					}
			}
		}

		for (int i = 0; i < nCoin; i++)
			if (coins[i].getStatus() >= 1)
			{
				coins[i].setAlpha(std::max(0, coins[i].getAlphaValue() - 3));
			}

		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render map (DO NOT PUT THIS LINE OF CODE BEHIND ANY OBJECT RENDER COMMAND, OR YOUR OBJECT WILL BE OVERLAPPED)
		level.drawMap(gRenderer);

		// Render coin
		for (int i = 0; i < nCoin; i++)
			coins[i].render(gRenderer, frame / 4);
		++frame;
		if (frame / 4 == 22)
			frame = 0;

		// Render dot
		for (int i = 0; i < nDots; i++)
			dots[i].render(currentTime, gRenderer);

		// Render player
		player.render(player.getPlayerPosX(), player.getPlayerPosY(), gRenderer);

		SDL_Color textColor = {255, 255, 255, 255};
		// Render level count text texture
		{
			if (!levelCount.loadText("LEVEL " + std::to_string(levelNum), textColor, gRenderer, gFont))
			{
				std::cout << "Failed to load level count text texture\n";
			}
			levelCount.renderText(5, 20, gRenderer);
		}
		// Render death count text texture
		{
			if (!deathCount.loadText("DEATH: " + std::to_string(death), textColor, gRenderer, gFont))
			{
				std::cout << "Failed to load death count text texture\n";
			}
			deathCount.renderText(SCREEN_WIDTH - 5 - deathCount.getWidth(), 20, gRenderer);
		}
		// Render coin count text texture
		{
			if (!coinCount.loadText("Coins: " + std::to_string(unsavedCoin) + "/" + std::to_string(nCoin), textColor, gRenderer, gFont))
			{
				std::cout << "Failed to load coin count text texture\n";
			}
			coinCount.renderText(SCREEN_WIDTH / 2 - coinCount.getWidth() / 2, 20, gRenderer);
		}
		// Render timer count text texture
		{
			int hour, minute, second, t;
			int curTime = SDL_GetTicks();
			t = curTime % 1000;
			curTime /= 1000;
			second = curTime % 60;
			curTime /= 60;
			minute = curTime % 60;
			curTime /= 60;
			hour = curTime;
			t /= 10;
			if (!timer.loadText((hour < 10 ? "0" : "") + std::to_string(hour) + ":" + (minute < 10 ? "0" : "") + std::to_string(minute) + ":" + (second < 10 ? "0" : "") + std::to_string(second) + ":" + (t < 10 ? "0" : "") + std::to_string(t), textColor, gRenderer, gFont))
			{
				std::cout << "Failed to load timer text texture\n";
			}
			timer.renderText(SCREEN_WIDTH / 2 - timer.getWidth() / 2, 655, gRenderer);
		}

		// Update screen
		SDL_RenderPresent(gRenderer);
		if (win == true)
		{

			if (levelNum < LEVEL_NUMBER)
			{
				closeMedia();
				run(levelNum + 1);
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				if (!loadVictoryScreen())
				{
					std::cout << "Failed to load out Victory screen\n";
					return;
				}

				renderVictoryScreen();
				SDL_RenderPresent(gRenderer);
			}
			quit = 1;
		}
	}
	closeMedia();
}
void runMainMenu()
{
	//Main menu interface
	UI mainMenu(7, 0);
	mainMenu.loadTexture("Resources/main_menu.png", gRenderer, 0);
	mainMenu.loadTexture("Resources/button_playgame.png", gRenderer, 1);
	mainMenu.setTextureCoor(SCREEN_WIDTH / 2 - mainMenu.getTextureWidth(1) / 2, 200,1);
	mainMenu.loadTexture("Resources/button_playgame_1.png", gRenderer, 2);
	mainMenu.setTextureCoor(SCREEN_WIDTH / 2 - mainMenu.getTextureWidth(2) / 2, 200, 2);
	mainMenu.loadTexture("Resources/button_tutorial.png", gRenderer, 3);
	mainMenu.setTextureCoor(SCREEN_WIDTH / 2 - mainMenu.getTextureWidth(3) / 2, 350, 3);
	mainMenu.loadTexture("Resources/button_tutorial_1.png", gRenderer, 4);
	mainMenu.setTextureCoor(SCREEN_WIDTH / 2 - mainMenu.getTextureWidth(4) / 2, 350, 4);
	mainMenu.loadTexture("Resources/button_exit.png", gRenderer, 5);
	mainMenu.setTextureCoor(SCREEN_WIDTH / 2 - mainMenu.getTextureWidth(5) / 2, 500, 5);
	mainMenu.loadTexture("Resources/button_exit_1.png", gRenderer, 6);
	mainMenu.setTextureCoor(SCREEN_WIDTH / 2 - mainMenu.getTextureWidth(6) / 2, 500, 6);
	bool quit = 0;
	SDL_Event event;
	while (!quit)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		while (SDL_PollEvent(&event) != 0)
		{
			// User requests quit
			if (event.type == SDL_QUIT)
			{
				quit = true;
				exit(0);
			}

			// Handle input for the main menu
			if (event.type == SDL_MOUSEBUTTONUP && isMouseInside(x, y, mainMenu.getTextureX(1), mainMenu.getTextureY(1), mainMenu.getTextureWidth(1), mainMenu.getTextureHeight(1)))
			{
				mainMenu.free();
				Mix_PlayChannel(-1, gBell, 0);
				run(1);
				quit = 1;
			}
			else 
			if (event.type == SDL_MOUSEBUTTONUP && isMouseInside(x, y, mainMenu.getTextureX(5), mainMenu.getTextureY(5), mainMenu.getTextureWidth(5), mainMenu.getTextureHeight(5)))
			{
				Mix_PlayChannel(-1, gBell, 0);
				quit = 1;
			}
			else
			if (event.type == SDL_MOUSEBUTTONUP && isMouseInside(x, y, mainMenu.getTextureX(3), mainMenu.getTextureY(3), mainMenu.getTextureWidth(5), mainMenu.getTextureHeight(3)))
			{
				Mix_PlayChannel(-1, gBell, 0);
				std::cerr << "HAS STARTED TO RUN\n";
				runTutorialMenu();
				std::cerr << "RUN SUCCESSFULLY\n";
			}

		}
		if (quit == 1) break;
		//Render main manu

		mainMenu.renderTexture(0, gRenderer);
		mainMenu.renderTexture(1 + isMouseInside(x, y, mainMenu.getTextureX(1), mainMenu.getTextureY(1), mainMenu.getTextureWidth(1), mainMenu.getTextureHeight(1)), gRenderer);
		mainMenu.renderTexture(3 + isMouseInside(x, y, mainMenu.getTextureX(3), mainMenu.getTextureY(3), mainMenu.getTextureWidth(3), mainMenu.getTextureHeight(3)), gRenderer);
		mainMenu.renderTexture(5 + isMouseInside(x, y, mainMenu.getTextureX(5), mainMenu.getTextureY(5), mainMenu.getTextureWidth(5), mainMenu.getTextureHeight(5)), gRenderer);
		//Present the screen to window
		SDL_RenderPresent(gRenderer);
	}
	mainMenu.free();
	
}
void runTutorialMenu()
{
	//Tutorial menu interface
	UI tutorialMenu(1, 2);
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Color textColorC = { 237,28,36,255 };

	tutorialMenu.loadTexture("Resources/tutorial_menu.png",gRenderer,0);
	tutorialMenu.loadText("BACK TO MAIN MENU", textColor, gRenderer, gFont, 0);
	tutorialMenu.setTextCoor(SCREEN_WIDTH - tutorialMenu.getTextWidth(0) - 10, SCREEN_HEIGHT - tutorialMenu.getTextHeight(0) - 10, 0);
	tutorialMenu.loadText("BACK TO MAIN MENU", textColorC, gRenderer, gFont, 1);
	tutorialMenu.setTextCoor(SCREEN_WIDTH - tutorialMenu.getTextWidth(1) - 10, SCREEN_HEIGHT - tutorialMenu.getTextHeight(1) - 10, 1);
	bool quit = 0;
	SDL_Event event;
	while (!quit)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		while (SDL_PollEvent(&event) != 0)
		{
			// User requests quit
			if (event.type == SDL_QUIT)
			{

				quit = true;
				exit(0);
			}

			// Handle input for the main menu
			if (event.type == SDL_MOUSEBUTTONUP && isMouseInside(x, y, tutorialMenu.getTextX(0), tutorialMenu.getTextY(0), tutorialMenu.getTextWidth(0), tutorialMenu.getTextHeight(0)))
			{
				quit = true;
			}

		}
		if (quit == 1) break;
		//Render tutorial menu manu
		tutorialMenu.renderTexture(0, gRenderer);
		tutorialMenu.renderText(0 + isMouseInside(x, y, tutorialMenu.getTextX(0), tutorialMenu.getTextY(0), tutorialMenu.getTextWidth(0), tutorialMenu.getTextHeight(0)),gRenderer);

		//Present the screen to window
		SDL_RenderPresent(gRenderer);
		
	}
	tutorialMenu.free();
}
int main(int argc, char **argv)
{
	if (!init())
	{
		std::cout << "Failed to initialize!\n";
		return -1;
	}
	Mix_PlayMusic(gMusic, 1000);
	runMainMenu();
	// Free resources
	closeGame();
	return 0;
}
