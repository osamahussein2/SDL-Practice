#pragma once

#include "PlatformerObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public PlatformerObject
{
public:
	AnimatedGraphic();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();
	virtual void LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_);

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