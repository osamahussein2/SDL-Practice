#pragma once

#include "GameState.h"
#include "CollisionManager.h"
#include "Level.h"

class GameObject;
class SDLGameObject;
class Level;

class PlayState : public GameState
{
public:
	virtual ~PlayState() { delete level; }

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

private:
	static const string playID;

	CollisionManager collisionManager;

	vector<GameObject*> gameObjects;

	Level* level;
};