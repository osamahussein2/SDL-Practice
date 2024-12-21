#include "TileLayer.h"

TileLayer::TileLayer(int tileSize_, const vector<Tileset>& tilesets_) : position(0, 0), velocity(0, 0), tileSize(tileSize_),
tilesets(tilesets_)
{
}

void TileLayer::Update()
{
}

void TileLayer::Render()
{
}

void TileLayer::SetTileIDs(const vector<vector<int>>& data_)
{
	tileIDs = data_;
}

void TileLayer::SetTileSize(int tileSize_)
{
	tileSize = tileSize_;
}

Tileset TileLayer::GetTilesetByID(int tileID_)
{
	return Tileset();
}
