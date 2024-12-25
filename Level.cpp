#include "Level.h"
#include "TextureManager.h"
#include "Window.h"
#include "Layer.h"
#include "TileLayer.h"
#include <math.h>
#include <iostream>

Level::Level()
{

}

Level::~Level()
{
	for (int i = 0; i < layers.size(); i++)
	{
		delete layers[i];
	}

	layers.clear();
}

void Level::Update()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->Update(this);
	}
}

void Level::Render()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->Render();
	}
}

vector<Tileset>* Level::GetTilesets()
{
	return &tilesets;
}

vector<Layer*>* Level::GetLayers()
{
	return &layers;
}

vector<TileLayer*>* Level::GetCollisionLayers()
{
	return &collisionLayers;
}

const vector<TileLayer*>& Level::GetCollidableLayers()
{
	return collisionLayers;
}

Player* Level::GetPlayer()
{
	return player;
}

void Level::SetPlayer(Player* player_)
{
	player = player_;
}
