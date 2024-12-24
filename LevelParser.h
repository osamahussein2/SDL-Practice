#pragma once

#include <iostream>
#include <vector>
#include "tinyxml.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;

using namespace std;

class LevelParser
{
public:
	// Create a level by using ParseLevel function
	Level* ParseLevel(const char* levelFile_);

private:
	void ParseTilesets(TiXmlElement* tilesetRoot_, vector<Tileset>* tilesets_);
	void ParseTileLayer(TiXmlElement* tileElement_, vector<Layer*>* layers_, const vector<Tileset>* tilesets_,
		vector<TileLayer*>* collisionLayers_);
	void ParseTextures(TiXmlElement* textureRoot_);
	void ParseObjectLayer(TiXmlElement* objectElement_, vector<Layer*>* layers_);

	int tileSize, width, height;

	Level* level;
};