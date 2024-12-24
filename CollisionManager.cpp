#include "CollisionManager.h"
#include "BulletHandler.h"
#include "Collision.h"

void CollisionManager::CheckPlayerEnemyBulletCollision(Player* player_)
{
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = player_->GetPosition().GetX();
	pRect1->y = player_->GetPosition().GetY();
	pRect1->w = player_->GetWidth();
	pRect1->h = player_->GetHeight();

	for (int i = 0; i < TheBulletHandler::Instance()->GetEnemyBullets().size(); i++)
	{
		EnemyBullet* pEnemyBullet = TheBulletHandler::Instance()->GetEnemyBullets()[i];

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = pEnemyBullet->GetPosition().GetX();
		pRect2->y = pEnemyBullet->GetPosition().GetY();

		pRect2->w = pEnemyBullet->GetWidth();
		pRect2->h = pEnemyBullet->GetHeight();

		if (RectangleCollision(pRect1, pRect2))
		{
			if (!player_->IsDying() && !pEnemyBullet->IsDying())
			{
				pEnemyBullet->Collision();
				player_->Collision();
			}
		}

		delete pRect2;
	}

	delete pRect1;
}

void CollisionManager::CheckPlayerEnemyCollision(Player* player_, const vector<GameObject*>& objects_)
{
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = player_->GetPosition().GetX();
	pRect1->y = player_->GetPosition().GetY();
	pRect1->w = player_->GetWidth();
	pRect1->h = player_->GetHeight();

	for (int i = 0; i < objects_.size(); i++)
	{
		if (objects_[i]->Type() != std::string("Enemy") || !objects_[i]->Updating())
		{
			continue;
		}

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = objects_[i]->GetPosition().GetX();
		pRect2->y = objects_[i]->GetPosition().GetY();
		pRect2->w = objects_[i]->GetWidth();
		pRect2->h = objects_[i]->GetHeight();

		if (RectangleCollision(pRect1, pRect2))
		{
			if (!objects_[i]->IsDead() && !objects_[i]->IsDying())
			{
				player_->Collision();
			}
		}

		delete pRect2;
	}

	delete pRect1;
}

void CollisionManager::CheckEnemyPlayerBulletCollision(const vector<GameObject*>& objects_)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		GameObject* pObject = objects_[i];

		for (int j = 0; j < TheBulletHandler::Instance()->GetPlayerBullets().size(); j++)
		{
			if (pObject->Type() != std::string("Enemy") || !pObject->Updating())
			{
				continue;
			}

			SDL_Rect* pRect1 = new SDL_Rect();
			pRect1->x = pObject->GetPosition().GetX();
			pRect1->y = pObject->GetPosition().GetY();
			pRect1->w = pObject->GetWidth();
			pRect1->h = pObject->GetHeight();

			PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->GetPlayerBullets()[j];

			SDL_Rect* pRect2 = new SDL_Rect();
			pRect2->x = pPlayerBullet->GetPosition().GetX();
			pRect2->y = pPlayerBullet->GetPosition().GetY();
			pRect2->w = pPlayerBullet->GetWidth();
			pRect2->h = pPlayerBullet->GetHeight();

			if (RectangleCollision(pRect1, pRect2))
			{
				if (!pObject->IsDying() && !pPlayerBullet->IsDying())
				{
					pPlayerBullet->Collision();
					pObject->Collision();
				}

			}

			delete pRect1;
			delete pRect2;
		}
	}
}

void CollisionManager::CheckPlayerTileCollision(Player* player_, const vector<TileLayer*>& collisionLayers_)
{
	// Iterate through collision layers
	for (vector<TileLayer*>::const_iterator it = collisionLayers_.begin(); it != collisionLayers_.end(); ++it)
	{
		TileLayer* tileLayer = (*it);

		vector<vector<int>> tiles = tileLayer->GetTileIDs();

		// Get the layers position
		Vector2 layerPosition = tileLayer->GetPosition();

		int x, y, tileColumn, tileRow, tileID = 0;

		// Calculate position on tile map
		x = layerPosition.GetX() / tileLayer->GetTileSize();
		y = layerPosition.GetY() / tileLayer->GetTileSize();

		// If moving forward or upwards
		if (player_->GetVelocity().GetX() >= 0 || player_->GetVelocity().GetY() >= 0)
		{
			tileColumn = ((player_->GetPosition().GetX() + player_->GetWidth()) / tileLayer->GetTileSize());
			tileRow = ((player_->GetPosition().GetY() + player_->GetHeight()) / tileLayer->GetTileSize());
			tileID = tiles[tileRow + y][tileColumn + x];
		}

		// If moving backwards or downwards
		else if (player_->GetVelocity().GetX() < 0 || player_->GetVelocity().GetY() < 0)
		{
			tileColumn = player_->GetPosition().GetX() / tileLayer->GetTileSize();
			tileRow = player_->GetPosition().GetY() / tileLayer->GetTileSize();
			tileID = tiles[tileRow + y][tileColumn + x];
		}

		// If the tile ID isn't blank, then collide
		if (tileID != 0)
		{
			player_->Collision();
		}
	}
}
