#pragma once

#include "ShooterObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"

class MenuButton : public ShooterObject
{
public:
	MenuButton();

	virtual ~MenuButton() {}

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_);

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

	int callbackID;

	bool released;
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new MenuButton();
	}
};