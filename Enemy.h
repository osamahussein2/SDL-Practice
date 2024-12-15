#pragma once

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* loaderParams_);

	virtual void Draw();
	virtual void Update();
	virtual void Clean();
};