#pragma once

#include <iostream>
#include "GameState.h"
#include "ShooterObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "CollisionManager.h"

class GameObject;

class PlayState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

private:
	static const string playID;

	vector<GameObject*> gameObjects;

	CollisionManager collisionManager;

	Level* level;
};