#pragma once

#include "SDLGameObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void LoadGameObject(const LoaderParams* loaderParams_);

	int GetCallbackID();
	void SetCallback(void(*callback)());

private:

	enum ButtonStates
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void (*callbackFunction)();

	bool released;
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new MenuButton();
	}
};