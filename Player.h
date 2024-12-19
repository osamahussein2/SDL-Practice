#pragma once

#include "SDLGameObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:
	Player();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void LoadGameObject(const LoaderParams* loaderParams_);

private:
	void HandleInput();
};

class PlayerCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new Player();
	}
};