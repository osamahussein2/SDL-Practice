#include "TileLayer.h"
#include "Window.h"
#include "TextureManager.h"

typedef Window TheWindow;
typedef TextureManager TheTextureManager;

TileLayer::TileLayer(int tileSize_, const vector<Tileset>& tilesets_) : tileSize(tileSize_), tilesets(tilesets_),
position(0, 0), velocity(0, 0)
{
	numberOfColumns = TheWindow::WindowInstance()->GetWindowWidth() / tileSize;
	numberOfRows = TheWindow::WindowInstance()->GetWindowHeight() / tileSize;
}

void TileLayer::Update(Level* level_)
{
	if (position.GetX() < ((mapWidth * tileSize) - TheWindow::WindowInstance()->GetWindowWidth()) - tileSize)
	{
		velocity.SetX(TheWindow::WindowInstance()->GetScrollSpeed());
		position += velocity;

	}
	else
	{
		velocity.SetX(0);
	}
}

void TileLayer::Render()
{
	int x, y, x2, y2 = 0;

	x = position.GetX() / tileSize;
	y = position.GetY() / tileSize;

	/* To ensure that our tile drawing doesn't jump between tiles, but smoothly scrolls, we use a modulo calculation to
	get the remaining tile amount that we need to move by and use that to position our map */
	x2 = int(position.GetX()) % tileSize;
	y2 = int(position.GetY()) % tileSize;

	// Loop through the number of columns and rows
	for (int i = 0; i < numberOfRows; i++)
	{
		for (int j = 0; j < numberOfColumns; j++)
		{
			// Get the current tile ID from the array
			int ID = tileIDs[i][j + x];

			// Check if the tile ID is 0, and don't draw anything we don't want if that's the case
			if (ID == 0)
			{
				continue;
			}

			// Otherwise, grab the correct tileset
			Tileset tileset = GetTilesetByID(ID);

			// Decrement the ID so that we can draw the correct tile from the tilesheet, even if it is at position 0,0
			ID--;

			/* We use the DrawTile function to copy across the correct tile using the tileset we grabbed earlier, to set
			the first parameter of the function, which is the name of the texture. We can use the tileset for the next 2
			parameters, margin and spacing. The next 2 parameters set the position we want to draw our tiles at. Then, we
			can set the current x position as the current column multiplied by the width of a tile and the y value as the
			current row multiplied by the height of a tile. We then set the width and height of the tile we're copying
			across. And finally, we work out the location of the tile on the tilesheet. */
			TheTextureManager::TextureManagerInstance()->DrawTile(tileset.name, tileset.margin, tileset.spacing, 
				(j * tileSize) - x2, (i * tileSize) - y2, tileSize, tileSize, (ID - (tileset.firstGridID - 1)) / 
				tileset.numberOfColumns, (ID - (tileset.firstGridID - 1)) % tileset.numberOfColumns, 
				TheWindow::WindowInstance()->GetRenderer());
		}
	}
}

const vector<vector<int>>& TileLayer::GetTileIDs()
{
	return tileIDs;
}

void TileLayer::SetTileIDs(const vector<vector<int>>& data_)
{
	tileIDs = data_;
}

void TileLayer::SetMapWidth(int mapWidth_)
{
	mapWidth = mapWidth_;
}

int TileLayer::GetTileSize()
{
	return tileSize;
}

void TileLayer::SetTileSize(int tileSize_)
{
	tileSize = tileSize_;
}

Tileset TileLayer::GetTilesetByID(int tileID_)
{
	// Compare each tileset's firstgid value and return the correct tileset
	for (int i = 0; i < tilesets.size(); i++)
	{
		if (i + 1 <= tilesets.size() - 1)
		{
			if (tileID_ >= tilesets[i].firstGridID && tileID_ < tilesets[i + 1].firstGridID)
			{
				return tilesets[i];
			}
		}
		else
		{
			return tilesets[i];
		}
	}

	cout << "Did not find tileset, returning empty tileset\n";

	Tileset t;
	return t;
}

const Vector2 TileLayer::GetPosition()
{
	return position;
}
