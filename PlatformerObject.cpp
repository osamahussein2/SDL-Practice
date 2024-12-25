#include "PlatformerObject.h"
#include "TextureManager.h"
#include "Window.h"
#include "TileLayer.h"

PlatformerObject::PlatformerObject() : GameObject(), bulletFiringSpeed(0), bulletCounter(0), moveSpeed(0), dyingTime(0),
dyingCounter(0), playedDeathSound(false), flipped(false), moveLeft(false), moveRight(false), isRunning(false), 
isFalling(false), isJumping(false), canJump(false), lastSafePosition(0, 0)
{

}

void PlatformerObject::Draw()
{
	TextureManager::TextureManagerInstance()->DrawFrame(textureID, (Uint32)position.GetX(), (Uint32)position.GetY(),
		width, height, currentRow, currentFrame, TheWindow::WindowInstance()->GetRenderer(), angle, alpha, 
		SDL_FLIP_NONE);
}

void PlatformerObject::Update()
{
	position += velocity;

	currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % numberOfFrames));
}

void PlatformerObject::LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_)
{
	position = Vector2(loaderParams_->GetX(), loaderParams_->GetY());
	//velocity = Vector2(0, 0);
	//acceleration = Vector2(0, 0);

	width = loaderParams_->GetWidth();
	height = loaderParams_->GetHeight();
	textureID = loaderParams_->GetTextureID();
	numberOfFrames = loaderParams_->GetNumberOfFrames();
}

void PlatformerObject::DoDyingAnimation()
{
	// Keep scrolling with the map
	//Scroll(TheWindow::WindowInstance()->GetScrollSpeed());

	currentFrame = static_cast<int>(((SDL_GetTicks() / (1000 / 10)) % numberOfFrames));

	if (dyingCounter == dyingTime)
	{
		isDead = true;
	}

	dyingCounter++;
}

bool PlatformerObject::CheckCollideTile(Vector2 newPos_)
{
	// Makes sure that we can fall off the map without the function trying to access tiles that aren't there
	if (newPos_.y + height >= TheWindow::WindowInstance()->GetWindowHeight() - 32)
	{
		return false;
	}

	else
	{
		for (vector<TileLayer*>::iterator it = collisionLayers->begin(); it != collisionLayers->end(); ++it)
		{
			TileLayer* tileLayer = (*it);
			vector<vector<int>> tiles = tileLayer->GetTileIDs();

			Vector2 layerPosition = tileLayer->GetPosition();

			int x, y, tileColumn, tileRow, tileID = 0;

			x = layerPosition.GetX() / tileLayer->GetTileSize();
			y = layerPosition.GetY() / tileLayer->GetTileSize();

			Vector2 startPosition = newPos_;
			startPosition.x += 15;
			startPosition.y += 20;

			Vector2 endPosition(newPos_.x + (width - 15), (newPos_.y) + height - 4);

			for (int i = startPosition.x; i < endPosition.x; i++)
			{
				for (int j = startPosition.y; j < endPosition.y; j++)
				{
					tileColumn = i / tileLayer->GetTileSize();
					tileRow = j / tileLayer->GetTileSize();

					tileID = tiles[tileRow + y][tileColumn + x];

					if (tileID != 0)
					{
						return true;
					}
				}
			}
		}

		return false;
	}
}