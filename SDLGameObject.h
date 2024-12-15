#pragma once

#include "Window.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* loaderParams_);

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

protected:
	int x, y;
	int width, height;
	int currentRow, currentFrame;
	string textureID;
};