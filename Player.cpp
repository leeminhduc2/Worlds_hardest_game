#include "common.h"
#include "Player.hpp"
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