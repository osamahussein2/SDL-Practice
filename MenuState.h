#pragma once

#include <iostream>
#include "GameState.h"
#include "GameObject.h"

using namespace std;

class MenuState : public GameState
{
protected:
	typedef void (*Callback) ();
	virtual void SetCallbacks(const vector<Callback>& callbacks_) = 0;

	vector<Callback> callbacks;
};

class MainMenuState : public MenuState
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

	virtual void SetCallbacks(const vector<Callback>& callbacks_);

	// Callback functions for menu items (callback functionality only support static functions)
	static void MenuToPlay();
	static void ExitFromMenu();
};