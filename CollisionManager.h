#pragma once

#include "Player.h"
#include "GameObject.h"
#include "TileLayer.h"

class CollisionManager
{
public:
	void CheckPlayerEnemyBulletCollision(Player* player_);
	void CheckPlayerEnemyCollision(Player* player_, const vector<GameObject*> &objects_);
	void CheckEnemyPlayerBulletCollision(const vector<GameObject*> &objects_);
	void CheckPlayerTileCollision(Player* player_, const vector<TileLayer*> &collisionLayers_);
};