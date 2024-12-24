#pragma once

#include <iostream>
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "MenuState.h"

class GameObject;

class GameOverState : public MenuState
{
public:
	virtual ~GameOverState() {}

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

	virtual void SetCallbacks(const vector<Callback>& callbacks_);

private:
	static void GameOverToMain();
	static void RestartPlay();

	static const string gameOverID;

	vector<GameObject*> gameObjects;
};