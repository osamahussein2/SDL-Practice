#pragma once

#include "SDLGameObject.h"
#include "InputHandler.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* loaderParams_);

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

private:
	void HandleInput();
};