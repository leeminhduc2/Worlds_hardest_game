#include "common.h"
#include "Player.hpp"
#include "Level.hpp"

Player::Player()
{
	// Initialize the initial position
	pPosX = 125;
	pPosY = 360;

	// Initialize the player dimension
	pHeight = 0;
	pWidth = 0;

	// Initialize the velocity
	pVelX = 0;
	pVelY = 0;

	// Initialize the texture
	pTexture = NULL;

	// Initialize player status
	pStatus = playerStatus::ALIVE;

	// Initialize opacity with maximum percentage
	pAlphaValue = 255;
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
		pStatus = playerStatus::ALIVE;
		pAlphaValue = 255;
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

void Player::move(Level level)
{
	// Move to the right or left
	pPosX += pVelX;

	// If the player move out of the screen
	if (pPosX < 0 || pPosX + PLAYER_WIDTH > SCREEN_WIDTH)
	{
		// Undo moves
		pPosX -= pVelX;
	}
	else
	{
		bool ok = 1;

		// Checks if the upper left corner coincides with the background
		if (!level.getMapValue2(pPosY, pPosX))
			ok = 0;

		// Checks if the upper right corner coincides with the background
		if (!level.getMapValue2(pPosY + PLAYER_WIDTH - 1, pPosX))
			ok = 0;

		// Checks if the lower left corner coincides with the background
		if (!level.getMapValue2(pPosY, pPosX + PLAYER_HEIGHT - 1))
			ok = 0;

		// Checks if the lower left corner coincides with the background
		if (!level.getMapValue2(pPosY + PLAYER_WIDTH - 1, pPosX + PLAYER_HEIGHT - 1))
			ok = 0;

		if (!ok)
		{
			// Undo moves
			pPosX -= pVelX;
		}
	}

	pPosY += pVelY;

	// If the player move out of the screen
	if (pPosY < 0 || pPosY + PLAYER_HEIGHT > SCREEN_HEIGHT)
	{
		// Undo moves
		pPosY -= pVelY;
	}
	else
	{
		bool ok = 1;

		// Checks if the upper left corner coincides with the background
		if (!level.getMapValue2(pPosY, pPosX))
			ok = 0;

		// Checks if the upper right corner coincides with the background
		if (!level.getMapValue2(pPosY + PLAYER_WIDTH - 1, pPosX))
			ok = 0;

		// Checks if the lower left corner coincides with the background
		if (!level.getMapValue2(pPosY, pPosX + PLAYER_HEIGHT - 1))
			ok = 0;

		// Checks if the lower left corner coincides with the background
		if (!level.getMapValue2(pPosY + PLAYER_WIDTH - 1, pPosX + PLAYER_HEIGHT - 1))
			ok = 0;

		if (!ok)
		{
			// Undo moves
			pPosY -= pVelY;
		}
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

void Player::setPStatus(bool currentStatus)
{
	pStatus = currentStatus;
}

void Player::setBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(pTexture, blending);
}

void Player::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(pTexture, alpha);
	pAlphaValue = alpha;
}

bool Player::checkCollision(int currentTime, Dot dot)
{
	// Finds the current coordinate of the dot
	currentTime %= dot.getTotalTime();
	int dX, dY;
	for (int i = 0; i < (int)dot.getPatternSize(); i++)
	{
		if (currentTime > dot.getMoveTime(i))
		{
			currentTime -= dot.getMoveTime(i);
		}
		else
		{
			dX = dot.getXS(i) + (dot.getXF(i) - dot.getXS(i)) * currentTime / dot.getMoveTime(i);
			dY = dot.getYS(i) + (dot.getYF(i) - dot.getYS(i)) * currentTime / dot.getMoveTime(i);
			break;
		}
	}
	dX+=dot.C_RAD;
	dY+=dot.C_RAD;
	// Finds the minimum distance from the dots center to the player's edge
	double dist = 2000.0;
	if ((pPosX <= dX && dX < (pPosX + pWidth)) && (pPosY <= dY && dY < pPosY + pHeight))
		dist = 0.1;
	if ((pPosX <= dX && dX < pPosX + pWidth))
		dist = std::min({dist, 1.0 * abs(dY - pPosY), 1.0 * abs(dY - (pPosY + pHeight - 1))});
	if ((pPosY <= dY && dY < pPosY + pHeight))
		dist = std::min({dist, 1.0 * abs(dX - pPosX), 1.0 * abs(dX - (pPosX + pWidth - 1))});
	dist = std::min(dist, sqrt(1.0 * (pPosX - dX) * (pPosX - dX) + 1.0 * (pPosY - dY) * (pPosY - dY)));
	dist = std::min(dist, sqrt(1.0 * (pPosX + pWidth - 1 - dX) * (pPosX + pWidth - 1 - dX) + 1.0 * (pPosY - dY) * (pPosY - dY)));
	dist = std::min(dist, sqrt(1.0 * (pPosX - dX) * (pPosX - dX) + 1.0 * (pPosY + pHeight - 1 - dY) * (pPosY + pHeight - 1 - dY)));
	dist = std::min(dist, sqrt(1.0 * (pPosX + pWidth - 1 - dX) * (pPosX + pWidth - 1 - dX) + 1.0 * (pPosY + pHeight - 1 - dY) * (pPosY + pHeight - 1 - dY)));
	return (dist <= 1.0 * dot.C_RAD);
	
}

int Player::getAlphaValue()
{
	return pAlphaValue;
}

bool Player::getPlayerStatus()
{
	return pStatus;
}

void Player::setPosX(int val)
{
	pPosX = val;
}

void Player::setPosY(int val)
{
	pPosY = val;
}