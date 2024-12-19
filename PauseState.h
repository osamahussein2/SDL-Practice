#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Window.h"
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
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

	virtual void SetCallbacks(const vector<Callback>& callbacks_);

	static const string pauseID;

	vector<GameObject*> gameObjects;
};