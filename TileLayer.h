#pragma once

#include "Layer.h"
#include "Level.h"
#include "Vector2.h"

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize_, const vector<Tileset>& tilesets_);

	virtual void Update();
	virtual void Render();

	void SetTileIDs(const vector<vector<int>>& data_);
	void SetTileSize(int tileSize_);

	Tileset GetTilesetByID(int tileID_);

private:
	int numberOfColumns, numberOfRows, tileSize;

	// Vector2 variables here are used to scroll the map
	Vector2 position, velocity;

	const vector<Tileset>& tilesets;
	vector<vector<int>> tileIDs;
};