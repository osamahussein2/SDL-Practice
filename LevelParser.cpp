#include "LevelParser.h"
#include "TextureManager.h"
#include "Window.h"
#include "TileLayer.h"
#include "base64.h"
#include <zlib.h>

typedef TextureManager TheTextureManager;
typedef Window TheWindow;

// LevelParser has access to the private constructor of Level and can return new instances of it
Level* LevelParser::ParseLevel(const char* levelFile_)
{
	// Create an XML document and load the map XML
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile_);

	// Create the Level object
	Level* level = new Level();

	// Get the root node
	TiXmlElement* root = levelDocument.RootElement();

	// Grab the attribute strings from the XML and set the member variables for LevelParser
	root->Attribute("tilewidth", &tileSize);
	root->Attribute("width", &width);
	root->Attribute("height", &height);

	// Parse the tilesets
	for (TiXmlElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		// Check for tileset nodes and parse them
		if (element->Value() == string("tileset"))
		{
			ParseTilesets(element, level->GetTilesets());
		}
	}
	
	// Parse any object layers
	for (TiXmlElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		// Check for layer nodes and parse them
		if (element->Value() == string("layer"))
		{
			ParseTileLayer(element, level->GetLayers(), level->GetTilesets());
		}
	}

	return level;
}

void LevelParser::ParseTilesets(TiXmlElement* tilesetRoot_, vector<Tileset>* tilesets_)
{
	// Add the tileset to texture manager
	TheTextureManager::TextureManagerInstance()->LoadTexture(tilesetRoot_->FirstChildElement()->Attribute("source"),
		tilesetRoot_->Attribute("name"), TheWindow::WindowInstance()->GetRenderer());

	// Create a tileset object
	Tileset tileset;
	tilesetRoot_->FirstChildElement()->Attribute("width", &tileset.width);
	tilesetRoot_->FirstChildElement()->Attribute("height", &tileset.height);
	tilesetRoot_->FirstChildElement()->Attribute("firstgid", &tileset.firstGridID);
	tilesetRoot_->FirstChildElement()->Attribute("tilewidth", &tileset.tileWidth);
	tilesetRoot_->FirstChildElement()->Attribute("tileheight", &tileset.tileHeight);
	tilesetRoot_->FirstChildElement()->Attribute("spacing", &tileset.spacing);
	tilesetRoot_->FirstChildElement()->Attribute("margin", &tileset.margin);

	tileset.name = tilesetRoot_->Attribute("name");

	tileset.numberOfColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	tilesets_->push_back(tileset);
}

void LevelParser::ParseTileLayer(TiXmlElement* tileElement_, vector<Layer*>* layers_, const vector<Tileset>* tilesets_)
{
	// Create a new instance of TileLayer
	TileLayer* tileLayer = new TileLayer(tileSize, *tilesets_);

	// A multidimensional array of int values to hold our final decoded and uncompressed tile data
	vector<vector<int>> tileData;

	// A string that will be our base64 decoded information and a place to store our XML node once we find it
	string decodedIDs;
	TiXmlElement* dataNode{};

	for (TiXmlElement* element = tileElement_->FirstChildElement(); element != NULL; 
		element = element->NextSiblingElement())
	{
		// Search for the data node
		if (element->Value() == string("data"))
		{
			dataNode = element;
		}
	}

	for (TiXmlNode* node = dataNode->FirstChild(); node != NULL; node = node->NextSibling())
	{
		/* Once we have found the correct node, then we can get the text from within it(our encoded / compressed data)
		and use the base64 decoder to decode it */
		TiXmlText* text = node->ToText();
		string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// Uncompress zlib compression
	uLongf numberOfGids = width * height * sizeof(int);
	vector<unsigned> gids(numberOfGids);

	// Use the zlib library to decompress our data by using uncompress function

	/* The uncompress function takes an array of Bytef* (defined in zlib's zconf.h) as the destination buffer, by doing 
	that we're using an std::vector of int values and casting it to a Bytef* array. The second parameter is the total
	size of the destination buffer, in this case we're using a vector of int values making the total size the number
	of rows x the number of columns x the size of an int, or width * height * sizeof(int). Then, we pass in our decoded
	string and its size as the final 2 parameters. */
	uncompress((Bytef*)&gids[0], &numberOfGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	/* The IDs vector now contains all of our tile IDs and the function moves on to set the size of our data vector for
	us to fill with our tile IDs */

	vector<int> layerRow(width);

	for (int j = 0; j < height; j++)
	{
		tileData.push_back(layerRow);
	}

	// Fill the data array with the correct values
	for (int rows = 0; rows < height; rows++)
	{
		for (int columns = 0; columns < width; columns++)
		{
			tileData[rows][columns] = gids[rows * width + columns];
		}
	}

	// Set the layer's tile data and then push the layer into the layers array of our Level
	tileLayer->SetTileIDs(tileData);
	layers_->push_back(tileLayer);
}
