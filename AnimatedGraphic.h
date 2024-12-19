#pragma once

#include "SDLGameObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();
	virtual void LoadGameObject(const LoaderParams* loaderParams_);

private:
	int animationSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new AnimatedGraphic();
	}
};