#pragma once

#include <iostream>
#include <vector>

class Player;
class GameObject;
class TileLayer;

using namespace std;

class CollisionManager
{
public:
	//void CheckPlayerEnemyBulletCollision(Player* player_);
	void CheckPlayerEnemyCollision(Player* player_, const vector<GameObject*> &objects_);
	//void CheckEnemyPlayerBulletCollision(const vector<GameObject*> &objects_);
	//void CheckPlayerTileCollision(Player* player_, const vector<TileLayer*> &collisionLayers_);
};