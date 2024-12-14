#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <map>

using namespace std;

// A singleton is a class that can only have one instance (meaning we can reuse this class throughout the game)
class TextureManager
{
private:
	TextureManager() : tempSurface(nullptr), texture(nullptr), textureLoaded(false), srcRectangle(SDL_Rect()),
		destRectangle(SDL_Rect()) {};

public:
	~TextureManager();

	static TextureManager* TextureManagerInstance();

	bool LoadTexture(string fileName_, string ID_, SDL_Renderer* rend_);
	void DrawTexture(string ID_, int x_, int y_, int width_, int height_, SDL_Renderer* rend_, SDL_RendererFlip flip_);
	void DrawFrame(string ID_, int x_, int y_, int width_, int height_, int currentRow_, int currentFrame_, 
		SDL_Renderer* rend_, SDL_RendererFlip flip_);

private:

	// Map of pointers to the SDL_Texture objects, keyed using strings
	map<string, SDL_Texture*> textureMap;

	SDL_Surface* tempSurface;
	SDL_Texture* texture;

	bool textureLoaded;

	SDL_Rect srcRectangle; // first rectangle (the source rectangle)
	SDL_Rect destRectangle; // another rectangle (the destination rectangle)

	static TextureManager* textureManagerInstance;
};