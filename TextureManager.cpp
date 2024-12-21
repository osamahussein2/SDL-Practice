#include "TextureManager.h"

TextureManager* TextureManager::textureManagerInstance = 0;

TextureManager::~TextureManager()
{
	tempSurface = nullptr;
	texture = nullptr;

	textureLoaded = false;
}

TextureManager* TextureManager::TextureManagerInstance()
{
	// If we don't have an instance of texture manager, create one using the class constructor
	if (textureManagerInstance == 0)
	{
		textureManagerInstance = new TextureManager();
		return textureManagerInstance;
	}

	return textureManagerInstance;
}

bool TextureManager::LoadTexture(string fileName_, string ID_, SDL_Renderer* rend_)
{
	// Load the texture file using the SDL's surface object
	tempSurface = IMG_Load(fileName_.c_str());

	if (tempSurface == NULL)
	{
		textureLoaded = false;
	}

	// Use the texture to render from the SDL's surface
	texture = SDL_CreateTextureFromSurface(rend_, tempSurface);

	// Free the surface to release any used memory
	SDL_FreeSurface(tempSurface);

	// Get the dimensions of the texture here and use it to set the width and height of the image
	//SDL_QueryTexture(spriteTexture, NULL, NULL, &srcRectangle.w, &srcRectangle.h);

	if (texture != 0)
	{
		textureMap[ID_] = texture;
		textureLoaded = true;
	}

	return textureLoaded;
}

void TextureManager::DrawTexture(string ID_, int x_, int y_, int width_, int height_, SDL_Renderer* rend_,
	SDL_RendererFlip flip_)
{
	// By setting the source rectangle, the SDL renderer will know which section of the image to draw to the renderer
	srcRectangle.x = 0;
	srcRectangle.y = 0;

	// By setting the destination rectangle, the SDL renderer will know where to draw the image inside the window
	srcRectangle.w = destRectangle.w = width_;
	srcRectangle.h = destRectangle.h = height_;

	// Determines the location that we want the pixels inside the source rectangle to be copied to
	destRectangle.x = x_;
	destRectangle.y = y_;

	/* SDL_RenderCopyEx function takes the same parameter as SDL_RenderCopy but also passes in parameters for
	rotation and flipping. The 4th parameter is the angle we want the image to be displayed with parameter 5 being
	the center point we want for the rotation. The 6th (final) parameter is an enumerated type called SDL_RendererFlip */
	SDL_RenderCopyEx(rend_, textureMap[ID_], &srcRectangle, &destRectangle, 0, 0, flip_);
}

void TextureManager::DrawFrame(string ID_, int x_, int y_, int width_, int height_, int currentRow_, int currentFrame_,
	SDL_Renderer* rend_, SDL_RendererFlip flip_)
{
	srcRectangle.x = width_ * currentFrame_;
	srcRectangle.y = height_ * currentRow_;
	srcRectangle.w = destRectangle.w = width_;
	srcRectangle.h = destRectangle.h = height_;

	destRectangle.x = x_;
	destRectangle.y = y_;

	// Render the loaded texture to the window
	//SDL_RenderCopy(gameRenderer, spriteTexture, &srcRectangle, &destRectangle);

	//SDL_RenderCopy(gameRenderer, spriteTexture, 0, 0); // Render the entire texture

	SDL_RenderCopyEx(rend_, textureMap[ID_], &srcRectangle, &destRectangle, 0, 0, flip_);
}

void TextureManager::DrawTile(string ID_, int margin_, int spacing_, int x_, int y_, int width_, int height_, 
	int currentRow_, int currentFrame_, SDL_Renderer* rend_)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = margin_ + (spacing_ + width_) * currentFrame_;
	srcRect.y = margin_ + (spacing_ + height_) * currentRow_;
	srcRect.w = destRect.w = width_;
	srcRect.h = destRect.h = height_;

	destRect.x = x_;
	destRect.y = y_;

	SDL_RenderCopyEx(rend_, textureMap[ID_], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::ClearFromTextureMap(string ID_)
{
	textureMap.erase(ID_);
}