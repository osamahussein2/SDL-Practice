#pragma once

#include <iostream>
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Window.h"

using namespace std;

class MenuState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

private:
	static const string menuID;

	vector<GameObject*> gameObjects;

	// Callback functions for menu items (callback functionality only support static functions)
	static void MenuToPlay();
	static void ExitFromMenu();
};