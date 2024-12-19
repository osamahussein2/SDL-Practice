#pragma once

#include "Window.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void LoadGameObject(const LoaderParams* loaderParams_);

	Vector2& GetPosition() { return position; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

protected:
	Vector2 position, velocity, acceleration;
	int width, height;
	int currentRow, currentFrame;
	string textureID;
	int callbackID;
	int animationSpeed;
};