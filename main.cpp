/* leeminhduc2 - 23020047 - UET-VNU */

// Includes standard libraries
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Constants
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 800;

/*================ Player class and functions================*/
class Player
{
public:
	static const int PLAYER_WIDTH = 20;
	static const int PLAYER_HEIGHT = 20;

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
	void move();

	// Show player on the screen
	void render();

private:
	// The position of the red block
	int pPosX, pPosY;

	// The "player" dimension
	int pWidth, pHeight;

	// The velocity of the red block
	int pVelX, pVelY;

	// The actual hardware texture
	SDL_Texture *pTexture;
};
Player::Player()
{
	// Initialize the initial position
	pPosX = 0;
	pPosY = 0;

	// Initialize the player dimension
	pHeight = 0;
	pWidth = 0;

	// Initialize the velocity
	pVelX = 0;
	pVelY = 0;

	// Initialize the texture
	pTexture = NULL;
}

Player::~Player()
{
	free();
}

void Player::free()
{
	// Free texture if it exists
	if (pTexture != NULL)
	{
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
		pPosX = 0;
		pPosY = 0;
		pVelX = 0;
		pVelY = 0;
		pWidth = 0;
		pHeight = 0;
	}
}

bool Player::loadFile(std::string path, SDL_Renderer *gRenderer)
{
	// Remove the existing texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << "with exitcode " << IMG_GetError();
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture " << path.c_str() << "with exitcode " << SDL_GetError();
		}
		else
		{
			// Get image dimensions
			pWidth = loadedSurface->w;
			pHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	pTexture = newTexture;
	return pTexture != NULL;
}

void Player::render(int x, int y, SDL_Renderer *gRenderer, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Set up rendering space and render to screen
	SDL_Rect renderRect = {x, y, pWidth, pHeight};
	if (clip != NULL)
	{
		renderRect.w = clip->w;
		renderRect.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(gRenderer, pTexture, clip, &renderRect, angle, center, flip);
}

int Player::getPlayerHeight()
{
	return pHeight;
}

int Player::getPlayerWidth()
{
	return pWidth;
}

void Player::move()
{
	// Move to the right or left
	pPosX += pVelX;

	// If the player move out of the screen
	if (pPosX < 0 || pPosX + PLAYER_WIDTH > SCREEN_WIDTH)
	{
		// Undo moves
		pPosX -= pVelX;
	}

	pPosY += pVelY;

	// If the player move out of the screen
	if (pPosY < 0 || pPosY + PLAYER_HEIGHT > SCREEN_HEIGHT)
	{
		// Undo moves
		pPosY -= pVelY;
	}
}

void Player::handleEvent(SDL_Event &e)
{
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			pVelY -= PLAYER_VEL;
			break;
		case SDLK_DOWN:
			pVelY += PLAYER_VEL;
			break;
		case SDLK_LEFT:
			pVelX -= PLAYER_VEL;
			break;
		case SDLK_RIGHT:
			pVelX += PLAYER_VEL;
			break;
		case SDLK_w:
			pVelY -= PLAYER_VEL;
			break;
		case SDLK_s:
			pVelY += PLAYER_VEL;
			break;
		case SDLK_a:
			pVelX -= PLAYER_VEL;
			break;
		case SDLK_d:
			pVelX += PLAYER_VEL;
			break;
		}
	}
	// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			pVelY += PLAYER_VEL;
			break;
		case SDLK_DOWN:
			pVelY -= PLAYER_VEL;
			break;
		case SDLK_LEFT:
			pVelX += PLAYER_VEL;
			break;
		case SDLK_RIGHT:
			pVelX -= PLAYER_VEL;
			break;
		case SDLK_w:
			pVelY += PLAYER_VEL;
			break;
		case SDLK_s:
			pVelY -= PLAYER_VEL;
			break;
		case SDLK_a:
			pVelX += PLAYER_VEL;
			break;
		case SDLK_d:
			pVelX -= PLAYER_VEL;
			break;
		}
	}
}

int Player::getPlayerPosX()
{
	return pPosX;
}
int Player::getPlayerPosY()
{
	return pPosY;
}
/*================ End of Player class and functions================*/

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

		// Render objects
		player.render(player.getPlayerPosX(), player.getPlayerPosY(), gRenderer);

		// Update screen
		SDL_RenderPresent(gRenderer);
	}

	// Free resources
	close();
}