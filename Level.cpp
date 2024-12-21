#include "Level.h"

Level::Level()
{

}

void Level::Update()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->Update();
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