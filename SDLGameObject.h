#pragma once

#include "Window.h"
#include "Vector2.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* loaderParams_);

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	Vector2& GetPosition() { return position; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

protected:
	Vector2 position, velocity, acceleration;
	int width, height;
	int currentRow, currentFrame;
	string textureID;
};