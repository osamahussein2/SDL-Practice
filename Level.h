#pragma once

#include <iostream>
#include <vector>

#include "Layer.h"
#include "LevelParser.h"
#include "Player.h"
#include "CollisionManager.h"

using namespace std;

// This struct holds information we need to know about tilesets
struct Tileset
{
	int firstGridID, tileWidth, tileHeight, spacing, margin, width, height, numberOfColumns;
	string name;
};

class Level
{
public:
	~Level() {}

	void Update();
	void Render();

	vector<Tileset>* GetTilesets();
	vector<Layer*>* GetLayers();
	vector<TileLayer*>* GetCollisionLayers();

	const vector<TileLayer*>& GetCollidableLayers();

	Player* GetPlayer() { return player; }
	void SetPlayer(Player* player_) { player = player_; }

private:

	/* To ensure that the ParseLevel function (found inside LevelParser.h) must be used to create a Level object, 
	the Level class' constructor should be private and make it a friend class of LevelParser */
	friend class LevelParser;
	Level();

	vector<Tileset> tilesets;
	vector<Layer*> layers;
	vector<TileLayer*> collisionLayers;

	Player* player;
};