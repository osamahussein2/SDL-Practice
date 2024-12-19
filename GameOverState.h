#pragma once

#include <iostream>
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "MenuState.h"
#include "MenuButton.h"

class GameObject;

class GameOverState : public MenuState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

private:
	static void GameOverToMain();
	static void RestartPlay();

	virtual void SetCallbacks(const vector<Callback>& callbacks_);

	static const string gameOverID;

	vector<GameObject*> gameObjects;
};