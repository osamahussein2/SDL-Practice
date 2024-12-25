#pragma once

#include <vector>
#include <iostream>
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:
	virtual ~PauseState() {}

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual string GetStateID() const;

	virtual void SetCallbacks(const vector<Callback>& callbacks_);

private:
	static void PauseToMain();
	static void ResumePlay();

	static const string pauseID;

	vector<GameObject*> gameObjects;
};