#include "common.h"
#include "Player.hpp"
#include "Level.hpp"
#include "Coin.hpp"
#include "Dot.hpp"

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

	// Initialize player status
	pStatus = playerStatus::ALIVE;

	// Initialize opacity with maximum percentage
	pAlphaValue = 255;

	// Initialize spawn point
	pSpawnPosX = 0;
	pSpawnPosY = 0;

	//Initialize moving states
	isUp = 0;
	isDown = 0;
	isLeft = 0;
	isRight = 0;

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
		pSpawnPosX = 0;
		pSpawnPosY = 0;
		isUp = 0;
	isDown = 0;
	isLeft = 0;
	isRight = 0;
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
		std::cout << "Unable to load image " << path.c_str() << "with exitcode " << IMG_GetError() << "\n";
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture " << path.c_str() << "with exitcode " << SDL_GetError() << "\n";
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
		if (e.key.keysym.sym==SDLK_UP&&!isUp)
			pVelY -= PLAYER_VEL,isUp=1;
		if (e.key.keysym.sym==SDLK_DOWN&&!isDown)
			pVelY += PLAYER_VEL,isDown=1;
		if (e.key.keysym.sym==SDLK_LEFT&&!isLeft)
			pVelX -= PLAYER_VEL,isLeft=1;
		if (e.key.keysym.sym==SDLK_RIGHT&&!isRight)
			pVelX += PLAYER_VEL,isRight=1;
		
	}
	// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// Adjust the velocity
		if (e.key.keysym.sym==SDLK_UP&&isUp)
			pVelY += PLAYER_VEL,isUp=0;
		if (e.key.keysym.sym==SDLK_DOWN&&isDown)
			pVelY -= PLAYER_VEL,isDown=0;
		if (e.key.keysym.sym==SDLK_LEFT&&isLeft)
			pVelX += PLAYER_VEL,isLeft=0;
		if (e.key.keysym.sym==SDLK_RIGHT&&isRight)
			pVelX -= PLAYER_VEL,isRight=0;
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
			if (dot.getIsCircular(i))
			{
				dX = dot.getXS(i) + (dot.getRad(i) * cos((dot.getXF(i) + (dot.getYF(i) - dot.getXF(i)) * (double(currentTime)) / dot.getMoveTime(i) )/ 180 * M_PI));
				dY = dot.getYS(i) + (dot.getRad(i) * sin((dot.getXF(i) + (dot.getYF(i) - dot.getXF(i)) * (double(currentTime)) / dot.getMoveTime(i)) / 180 * M_PI));
			}
			else
			{
				dX = dot.getXS(i) + (dot.getXF(i) - dot.getXS(i)) * currentTime / dot.getMoveTime(i);
				dY = dot.getYS(i) + (dot.getYF(i) - dot.getYS(i)) * currentTime / dot.getMoveTime(i);
			}
			
			break;
		}
	}
	dX += dot.C_RAD;
	dY += dot.C_RAD;
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
	return (dist <= 1.0 * 7.0);
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

bool Player::isTouchCoin(Coin &coin)
{
	// Finds the center coordinate of the dot

	int cX, cY;

	cX = coin.getX() + coin.COIN_RAD;
	cY = coin.getY() + coin.COIN_RAD;

	// Finds the minimum distance from the dots center to the player's edge
	double dist = 2000.0;
	if ((pPosX <= cX && cX < (pPosX + pWidth)) && (pPosY <= cY && cY < pPosY + pHeight))
		dist = 0.1;
	if ((pPosX <= cX && cX < pPosX + pWidth))
		dist = std::min({dist, 1.0 * abs(cY - pPosY), 1.0 * abs(cY - (pPosY + pHeight - 1))});
	if ((pPosY <= cY && cY < pPosY + pHeight))
		dist = std::min({dist, 1.0 * abs(cX - pPosX), 1.0 * abs(cX - (pPosX + pWidth - 1))});
	dist = std::min(dist, sqrt(1.0 * (pPosX - cX) * (pPosX - cX) + 1.0 * (pPosY - cY) * (pPosY - cY)));
	dist = std::min(dist, sqrt(1.0 * (pPosX + pWidth - 1 - cX) * (pPosX + pWidth - 1 - cX) + 1.0 * (pPosY - cY) * (pPosY - cY)));
	dist = std::min(dist, sqrt(1.0 * (pPosX - cX) * (pPosX - cX) + 1.0 * (pPosY + pHeight - 1 - cY) * (pPosY + pHeight - 1 - cY)));
	dist = std::min(dist, sqrt(1.0 * (pPosX + pWidth - 1 - cX) * (pPosX + pWidth - 1 - cX) + 1.0 * (pPosY + pHeight - 1 - cY) * (pPosY + pHeight - 1 - cY)));
	return (dist <= 1.0 * coin.COIN_RAD);
}

void Player::setSpawnPoint(int x, int y)
{
	pSpawnPosX = x;
	pSpawnPosY = y;
}

void Player::gotoSpawnPoint()
{
	pPosX = pSpawnPosX;
	pPosY = pSpawnPosY;
}

bool Player::isTouchTile(Level level, int value)
{
	// Checks if the upper left corner coincides with the background
	if (level.getMapValue2(pPosY, pPosX)==value)
		return 1;

	// Checks if the upper right corner coincides with the background
	if (level.getMapValue2(pPosY + PLAYER_WIDTH - 1, pPosX)==value)
		return 1;

	// Checks if the lower left corner coincides with the background
	if (level.getMapValue2(pPosY, pPosX + PLAYER_HEIGHT - 1)==value)
		return 1;

	// Checks if the lower left corner coincides with the background
	if (!level.getMapValue2(pPosY + PLAYER_WIDTH - 1, pPosX + PLAYER_HEIGHT - 1)==value)
		return 1;
	return 0;
}

void Player::getInfo()
{
	std::cerr << pPosX << " " << pVelX << " " << pPosY << " " << pVelY << "\n";
}
