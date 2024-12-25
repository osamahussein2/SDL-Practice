#pragma once

#include <iostream>
#include <vector>

#include "Layer.h"
#include "CollisionManager.h"

class GameObject;

using namespace std;

class ObjectLayer : public Layer
{
public:
	virtual ~ObjectLayer();

	virtual void Update(Level* level_);
	virtual void Render();

	vector<GameObject*>* GetGameObjects();

private:
	CollisionManager collisionManager;

	vector<GameObject*> gameObjects;
};