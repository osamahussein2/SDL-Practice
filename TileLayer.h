#pragma once

#include <vector>
#include <iostream>
#include "Layer.h"
#include "Level.h"
#include "Vector2.h"

using namespace std;

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize_, int mapWidth_, int mapHeight_, const vector<Tileset>& tilesets_);

	virtual ~TileLayer() {}

	virtual void Update(Level* level_);
	virtual void Render();

	const vector<vector<int>>& GetTileIDs();
	void SetTileIDs(const vector<vector<int>>& data_);

	int GetMapWidth();
	void SetMapWidth(int mapWidth_);

	int GetTileSize();
	void SetTileSize(int tileSize_);

	Tileset GetTilesetByID(int tileID_);

	const Vector2 GetPosition();

private:
	int numberOfColumns, numberOfRows, tileSize;
	int mapWidth;

	// Vector2 variables here are used to scroll the map
	Vector2 position, velocity;

	const vector<Tileset>& tilesets;
	vector<vector<int>> tileIDs;
};