#pragma once

#include <iostream>
#include "GameState.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Window.h"

class GameObject;

class PlayState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

	bool CheckCollision(SDLGameObject* p1, SDLGameObject* p2);

private:
	static const string playID;

	vector<GameObject*> gameObjects;
};