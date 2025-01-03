#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SDL.h>

using namespace std;

// A singleton is a class that can only have one instance (meaning we can reuse this class throughout the game)
class TextureManager
{
public:

	static TextureManager* TextureManagerInstance();

	bool LoadTexture(string fileName_, string ID_, SDL_Renderer* rend_);
	void DrawTexture(string ID_, int x_, int y_, int width_, int height_, SDL_Renderer* rend_, SDL_RendererFlip flip_);
	void DrawFrame(string ID_, int x_, int y_, int width_, int height_, int currentRow_, int currentFrame_, 
		SDL_Renderer* rend_, double angle_, int alpha_, SDL_RendererFlip flip_);
	void DrawTile(string ID_, int margin_, int spacing_, int x_, int y_, int width_, int height_, int currentRow_,
		int currentFrame_, SDL_Renderer* rend_);

	void ClearTextureMap();
	void ClearFromTextureMap(string ID_);

	map<string, SDL_Texture*> GetTextureMap();

private:

	TextureManager() : tempSurface(nullptr), texture(nullptr), textureLoaded(false), srcRectangle(SDL_Rect()),
		destRectangle(SDL_Rect()) {};
	~TextureManager();

	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

	// Map of pointers to the SDL_Texture objects, keyed using strings
	map<string, SDL_Texture*> textureMap;

	SDL_Surface* tempSurface;
	SDL_Texture* texture;

	bool textureLoaded;

	SDL_Rect srcRectangle; // first rectangle (the source rectangle)
	SDL_Rect destRectangle; // another rectangle (the destination rectangle)

	static TextureManager* textureManagerInstance;
};

typedef TextureManager TheTextureManager;