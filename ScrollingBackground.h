#pragma once

#include <iostream>
#include "PlatformerObject.h"
#include "GameObjectFactory.h"

class ScrollingBackground : public PlatformerObject
{
public:
	virtual ~ScrollingBackground() {}
	ScrollingBackground();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_);

private:

	int scrollSpeed;

	int count, maxCount;

	SDL_Rect srcRect1;
	SDL_Rect srcRect2;

	SDL_Rect destRect1;
	SDL_Rect destRect2;

	int srcRect1Width;
	int srcRect2Width;

	int destRect1Width;
	int destRect2Width;
};

class ScrollingBackgroundCreator : public BaseCreator
{
public:
	virtual GameObject* CreateGameObject() const
	{
		return new ScrollingBackground();
	}
};