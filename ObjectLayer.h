#pragma once

#include <vector>

#include "Layer.h"
#include "GameObject.h"

using namespace std;

class ObjectLayer : public Layer
{
public:
	virtual void Update();
	virtual void Render();

	vector<GameObject*>* GetGameObjects();
private:
	vector<GameObject*> gameObjects;
};