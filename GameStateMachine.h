#pragma once

#include <vector>
#include "GameState.h"

/* Finite state machine is going to need to handle the game states in a number of ways:

	1. Removing one state and adding another (Completely change states without leaving the option to return)

	2. Adding one state without removing the previous state (Useful for pause menus and so on)

	3. Removing one state without adding another (Remove pause states or other states that had been pushed on top of 
	another one)

*/

class GameStateMachine
{
public:
	GameStateMachine() {}
	~GameStateMachine() {}

	void PushState(GameState* gameState_);
	void ChangeState(GameState* gameState_);
	void PopState();

	void Update();
	void Render();
	void Clean();

	vector<GameState*>& GetGameStates() { return gameStates; }

private:
	// A vector of GameState pointer is needed to store the states
	vector<GameState*> gameStates;
};