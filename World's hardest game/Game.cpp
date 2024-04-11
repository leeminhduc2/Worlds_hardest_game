#include "common.h"

#include "Game.hpp"
#include "Player.hpp"
#include "Dot.hpp"
#include "Coin.hpp"
#include "HUD_Text.hpp"
#include "MovePath.hpp"

Game::Game(const SDL_Window* gWindow,const  SDL_Renderer* gRenderer, const TTF_Font* gFont)
{
	window = gWindow;
	renderer = gRenderer;
	font = gFont;
	
	player = Player();
	
	level = Level();
	
	dots = NULL;
	nDots = 0;

	coins = NULL;
	nCoin = curCoin = unsavedCoin = 0;

	deathCount =HUD_Text();
	death = 0;

	coinCount = HUD_Text();

	levelCount =HUD_Text();

	timer = HUD_Text();

	bell = NULL;
	smack = NULL;
	ding = NULL;

	isS = isK = isI = isP = isNR = 0;

	vTexture = NULL;

	//Load chunks
	bell = Mix_LoadWAV("Resources/Soundtracks/bell.wav");
	ding = Mix_LoadWAV("Resources/Soundtracks/ding.wav");
	smack = Mix_LoadWAV("Resources/Soundtracks/smack.wav");
	
	loadVictoryScreen();
}
Game::~Game()
{
	free();
}
void Game::free()
{
	Mix_FreeChunk(bell);
	Mix_FreeChunk(smack);
	Mix_FreeChunk(ding);
	bell = NULL;
	smack = NULL;
	ding = NULL;
}
bool Game::handleCheatCode(SDL_Event& e)
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
void Game::renderVictoryScreen()
{
	// Set up rendering space and render to screen
	SDL_Rect renderRect = { 0, 0, SCREEN_WIDTH, SCREEN_WIDTH };

	// Render to screen
	SDL_RenderCopy(renderer, vTexture, &renderRect, &renderRect);
}
bool Game::loadVictoryScreen()
{
	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image
	SDL_Surface* loadedSurface = IMG_Load("Resources/Victory_Screen.jpg");
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
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
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
bool Game::loadMedia(int levelNum)
{
	// Loading success flag
	bool success = 1;
	

	// Load level
	level.readLevelData("Resources/Level_datas/level" + std::to_string(levelNum) + ".txt");

	// Loads player
	if (!player.loadFile("Resources/Player.bmp", renderer))
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
			if (!coins[i].loadFromFile("Resources/coin_sheet.png", renderer))
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
			if (!dots[m].loadImage("Resources/Dot.bmp", renderer))
			{
				std::cout << "Failed to load out dot!\n";
				return 0;
			}

			int n;
			inp >> n;
			for (int i = 1; i <= n; i++)
			{

				double xF, xS, yF, yS, moveTime, rad;
				bool isCircular;
				inp >> xS >> yS >> xF >> yF >> moveTime >> isCircular >> rad;
				dots[m].addPath(xS, yS, xF, yF, moveTime, isCircular, rad);
			}
		}
		inp.close();
	}

	return success;
}
void Game::closeMedia()
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
void Game::run(int levelNum)
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
			}

			// Handle input for the dot
			player.handleEvent(event);
			if (handleCheatCode(event)) win = 1;
		}

		int currentTime = SDL_GetTicks();
		if (player.getPlayerStatus())
		{

			for (int j = 0; j < nDots; j++)
			{
				if (player.checkCollision(currentTime, dots[j]))
				{
					Mix_PlayChannel(-1, smack, 0);
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
					Mix_PlayChannel(-1, ding, 0);
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
							Mix_PlayChannel(-1, bell, 0);
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
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render map (DO NOT PUT THIS LINE OF CODE BEHIND ANY OBJECT RENDER COMMAND, OR YOUR OBJECT WILL BE OVERLAPPED)
		level.drawMap(renderer);

		// Render coin
		for (int i = 0; i < nCoin; i++)
			coins[i].render(renderer, frame / 4);
		++frame;
		if (frame / 4 == 22)
			frame = 0;

		// Render dot
		for (int i = 0; i < nDots; i++)
			dots[i].render(currentTime, renderer);

		// Render player
		player.render(player.getPlayerPosX(), player.getPlayerPosY(), renderer);

		SDL_Color textColor = { 255, 255, 255, 255 };
		// Render level count text texture
		{
			if (!levelCount.loadText("LEVEL " + std::to_string(levelNum), textColor, renderer, font))
			{
				std::cout << "Failed to load level count text texture\n";
			}
			levelCount.renderText(5, 20, renderer);
		}
		// Render death count text texture
		{
			if (!deathCount.loadText("DEATH: " + std::to_string(death), textColor, renderer, font))
			{
				std::cout << "Failed to load death count text texture\n";
			}
			deathCount.renderText(SCREEN_WIDTH - 5 - deathCount.getWidth(), 20, renderer);
		}
		// Render coin count text texture
		{
			if (!coinCount.loadText("Coins: " + std::to_string(unsavedCoin) + "/" + std::to_string(nCoin), textColor, renderer, font))
			{
				std::cout << "Failed to load coin count text texture\n";
			}
			coinCount.renderText(SCREEN_WIDTH / 2 - coinCount.getWidth() / 2, 20, renderer);
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
			if (!timer.loadText((hour < 10 ? "0" : "") + std::to_string(hour) + ":" + (minute < 10 ? "0" : "") + std::to_string(minute) + ":" + (second < 10 ? "0" : "") + std::to_string(second) + ":" + (t < 10 ? "0" : "") + std::to_string(t), textColor, renderer, font))
			{
				std::cout << "Failed to load timer text texture\n";
			}
			timer.renderText(SCREEN_WIDTH / 2 - timer.getWidth() / 2, 655, renderer);
		}

		// Update screen
		SDL_RenderPresent(renderer);
		if (win == true)
		{

			if (levelNum < LEVEL_NUMBER)
			{
				closeMedia();
				run(levelNum + 1);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);

				if (!loadVictoryScreen())
				{
					std::cout << "Failed to load out Victory screen\n";
					return;
				}

				renderVictoryScreen();
				SDL_RenderPresent(renderer);
			}
			quit = 1;
		}
	}
	closeMedia();
}