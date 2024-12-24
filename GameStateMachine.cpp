#include "GameStateMachine.h"

void GameStateMachine::PushState(GameState* gameState_)
{
	// Push the passed in game state into a pointer of game states
	gameStates.push_back(gameState_);

	// Call the OnEnter function after the state is pushed into the array
	gameStates.back()->OnEnter();
}

void GameStateMachine::ChangeState(GameState* gameState_)
{
	if (!gameStates.empty())
	{
		// If the state ID is the same as the current one, don't do anything by using the return keyword
		if (gameStates.back()->GetStateID() == gameState_->GetStateID())
		{
			return;
		}

		// Call OnExit of the current state if the state IDs don't match
		if (gameStates.back()->OnExit())
		{
			// Remove the game state
			delete gameStates.back();
			gameStates.pop_back();
		}
	}

	// Push back the newly passed in game state
	gameStates.push_back(gameState_);

	// Initialize that new state
	gameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
	// If the game states array is not empty (meaning it returns false)
	if (!gameStates.empty())
	{
		// Call OnExit of the current state
		if (gameStates.back()->OnExit())
		{
			// Remove the game state
			delete gameStates.back();
			gameStates.pop_back();
		}

		gameStates.back()->Resume();
	}
}

void GameStateMachine::Update()
{
	// If the game states array is not empty, then update the game state
	if (!gameStates.empty())
	{
		/* back() will get the current state since we designed the finite state machineto always use the state
		at the back of the array */
		gameStates.back()->Update();
	}
}

void GameStateMachine::Render()
{
	// If the game states array is not empty, then render the game state
	if (!gameStates.empty())
	{
		gameStates.back()->Render();
	}
}

void GameStateMachine::Clean()
{
	if (!gameStates.empty())
	{
		gameStates.back()->OnExit();

		delete gameStates.back();
		gameStates.clear();
	}
}
