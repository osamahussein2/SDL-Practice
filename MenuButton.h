#pragma once

#include "SDLGameObject.h"
#include "InputHandler.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton(const LoaderParams* loaderParams_, void(*callback)());

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

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