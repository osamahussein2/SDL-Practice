#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:
	Enemy();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void LoadGameObject(const LoaderParams* loaderParams_);
};

class EnemyCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new Enemy();
	}
};