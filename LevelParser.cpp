#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Window.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include <zlib.h>
#include "Level.h"

typedef GameObjectFactory TheGameObjectFactory;

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

	// Get the properties node
	TiXmlElement* properties = root->FirstChildElement();

	// Parse the textures
	for (TiXmlElement* element = properties->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		// Check for property nodes and parse the textures
		if (element->Value() == string("property"))
		{
			ParseTextures(element);
		}
	}

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
		if (element->Value() == string("objectgroup") || element->Value() == string("layer"))
		{
			if (element->FirstChildElement()->Value() == string("object"))
			{
				ParseObjectLayer(element, level->GetLayers(), level);
			}

			else if (element->FirstChildElement()->Value() == string("data") ||
				(element->FirstChildElement()->NextSiblingElement() != 0 && 
				element->FirstChildElement()->NextSiblingElement()->Value() == string("data")))
			{
				ParseTileLayer(element, level->GetLayers(), level->GetTilesets(), level->GetCollisionLayers());
			}
		}
	}

	return level;
}

void LevelParser::ParseTilesets(TiXmlElement* tilesetRoot_, vector<Tileset>* tilesets_)
{
	// Add the tileset to texture manager 
	string spritesTag = "Sprites/";

	/* tilesetRoot_->FirstChildElement()->Attribute("source") doesn't load the tilemap for me for some reason when 
	I pass it in the first parameter */
	TheTextureManager::TextureManagerInstance()->LoadTexture(spritesTag.append(tilesetRoot_->FirstChildElement()->Attribute
	("source")), tilesetRoot_->Attribute("name"), TheWindow::WindowInstance()->GetRenderer());

	// Create a tileset object
	Tileset tileset;
	tilesetRoot_->FirstChildElement()->Attribute("width", &tileset.width);
	tilesetRoot_->FirstChildElement()->Attribute("height", &tileset.height);
	tilesetRoot_->Attribute("firstgid", &tileset.firstGridID);
	tilesetRoot_->Attribute("tilewidth", &tileset.tileWidth);
	tilesetRoot_->Attribute("tileheight", &tileset.tileHeight);
	tilesetRoot_->Attribute("spacing", &tileset.spacing);
	tilesetRoot_->Attribute("margin", &tileset.margin);

	tileset.name = tilesetRoot_->Attribute("name");

	tileset.numberOfColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	tilesets_->push_back(tileset);
}

void LevelParser::ParseTextures(TiXmlElement* textureRoot_)
{
	TheTextureManager::TextureManagerInstance()->LoadTexture(textureRoot_->Attribute("value"),
		textureRoot_->Attribute("name"), TheWindow::WindowInstance()->GetRenderer());
}

void LevelParser::ParseObjectLayer(TiXmlElement* objectElement_, vector<Layer*>* layers_, Level* level_)
{
	ObjectLayer* objectLayer = new ObjectLayer();

	cout << objectElement_->FirstChildElement()->Value() << endl;

	for (TiXmlElement* element = objectElement_->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		cout << element->Value() << endl;

		if (element->Value() == string("object"))
		{
			int x, y, width, height, numberOfFrames, callbackID = 0, animationSpeed = 0;
			string textureID;
			string type;

			element->Attribute("x", &x);
			element->Attribute("y", &y);

			type = element->Attribute("type");
			GameObject* gameObject = TheGameObjectFactory::Instance()->Create(type);

			for (TiXmlElement* properties = element->FirstChildElement(); properties != NULL;
				properties = properties->NextSiblingElement())
			{
				if (properties->Value() == string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL;
						property = property->NextSiblingElement())
					{
						// Check for the name of the property
						if (property->Value() == string("property"))
						{
							if (property->Attribute("name") == string("numFrames"))
							{
								property->Attribute("value", &numberOfFrames);
							}

							else if (property->Attribute("name") == string("textureHeight"))
							{
								property->Attribute("value", &height);
							}

							else if (property->Attribute("name") == string("textureID"))
							{
								textureID = property->Attribute("value");
							}

							else if (property->Attribute("name") == string("textureWidth"))
							{
								property->Attribute("value", &width);
							}

							else if (property->Attribute("name") == string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}

							else if (property->Attribute("name") == string("animSpeed"))
							{
								property->Attribute("value", &animationSpeed);
							}
						}

					}
				}
			}

			// Create the game object and add it to object layer's game object array
			gameObject->LoadGameObject(unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID,
				numberOfFrames, callbackID, animationSpeed)));

			// Set the collision layers
			gameObject->SetCollisionLayers(level_->GetCollisionLayers());


			if (type == "Player")
			{
				level_->SetPlayer(dynamic_cast<Player*>(gameObject));
			}

			objectLayer->GetGameObjects()->push_back(gameObject);
		}
	}

	layers_->push_back(objectLayer);
}

void LevelParser::ParseTileLayer(TiXmlElement* tileElement_, vector<Layer*>* layers_, const vector<Tileset>* tilesets_,
	vector<TileLayer*>* collisionLayers_)
{
	// Create a new instance of TileLayer
	TileLayer* tileLayer = new TileLayer(tileSize, width, height, *tilesets_);

	// Local temporary variable
	bool collidable = false;

	// A multidimensional array of int values to hold our final decoded and uncompressed tile data
	vector<vector<int>> tileData;

	// A string that will be our base64 decoded information and a place to store our XML node once we find it
	string decodedIDs;
	TiXmlElement* dataNode = 0;

	for (TiXmlElement* element = tileElement_->FirstChildElement(); element != NULL;
		element = element->NextSiblingElement())
	{
		if (element->Value() == string("properties"))
		{
			for (TiXmlElement* property = element->FirstChildElement(); property != NULL;
				property = property->NextSiblingElement())
			{
				if (property->Value() == string("property"))
				{
					if (property->Attribute("name") == string("collidable"))
					{
						collidable = true;
					}
				}
			}
		}

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
	vector<int> gids(width * height);

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
	tileLayer->SetMapWidth(width);

	// Push into collision array if necessary
	if (collidable)
	{
		collisionLayers_->push_back(tileLayer);
	}

	layers_->push_back(tileLayer);
}
