#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Window.h"

class GameObject;

class PauseState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

private:
	static void PauseToMain();
	static void ResumePlay();

	static const string pauseID;

	vector<GameObject*> gameObjects;
};