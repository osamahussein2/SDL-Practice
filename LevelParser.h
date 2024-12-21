#pragma once

#include "tinyxml.h"
#include "Level.h"

class LevelParser
{
public:
	// Create a level by using ParseLevel function
	Level* ParseLevel(const char* levelFile_);

private:
	void ParseTilesets(TiXmlElement* tilesetRoot_, vector<Tileset>* tilesets_);
	void ParseTileLayer(TiXmlElement* tileElement_, vector<Layer*>* layers_, const vector<Tileset>* tilesets_);

	int tileSize, width, height;
};