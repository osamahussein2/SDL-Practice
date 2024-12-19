#pragma once

#include <string>
#include <vector>
#include "TextureManager.h"

using namespace std;

/* Definition of finite state machines (FSM) is a machine that can exist in a finite number of states, can exist in only
one state at a time (known as the current state), and can change from one state to another (known as a transition) */

/* This is an abstract base class since we're not putting any functionality into it, we just want our dervied classes
to follow this blueprint */

typedef TextureManager TheTextureManager;

class GameState
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	virtual void ClearTextures()
	{
		for (int i = 0; i < textureIDList.size(); i++)
		{
			TheTextureManager::TextureManagerInstance()->ClearFromTextureMap(textureIDList[i]);
		}
	}

	// ID is used to ensure that states don't get repeated
	virtual string GetStateID() const = 0;

protected:
	vector<string> textureIDList;
};