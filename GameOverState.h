#pragma once

#include <iostream>
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Window.h"

class GameObject;

class GameOverState : public GameState
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

	static const string gameOverID;

	vector<GameObject*> gameObjects;
};