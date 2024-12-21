#include "ObjectLayer.h"

void ObjectLayer::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

void ObjectLayer::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();
	}
}

vector<GameObject*>* ObjectLayer::GetGameObjects()
{
	return &gameObjects;
}
