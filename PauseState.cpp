#include "PauseState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "StateParser.h"

const string PauseState::pauseID = "PAUSE";

typedef InputHandler TheInputHandler;

void PauseState::Update()
{
	if (loadingComplete && !gameObjects.empty())
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update();
		}
	}
}

void PauseState::Render()
{
	if (loadingComplete && !gameObjects.empty())
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Draw();
		}
	}
}

bool PauseState::OnEnter()
{
	StateParser stateParser;

	// Parse the current state along with the XML file
	stateParser.ParseState("Attack.xml", pauseID, &gameObjects, &textureIDList);

	// Push callbacks into the array inherited from MenuState

	callbacks.push_back(0); // Push back 0 since callbackID start from 1
	callbacks.push_back(PauseToMain);
	callbacks.push_back(ResumePlay);

	// Set the callbacks for menu items
	SetCallbacks(callbacks);

	loadingComplete = true;

	cout << "entering PauseState" << endl;
	return true;
}

bool PauseState::OnExit()
{
	if (loadingComplete && !gameObjects.empty())
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Clean();
		}
	}

	gameObjects.clear();

	GameState::ClearTextures();

	TheInputHandler::InputHandlerInstance()->Reset();

	cout << "exiting PauseState" << endl;
	return true;
}

string PauseState::GetStateID() const
{
	return pauseID;
}

void PauseState::PauseToMain()
{
	// Go back to the main menu and completely remove any other states
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new MainMenuState());
}

void PauseState::ResumePlay()
{
	/* Once we are done with the pushed state, we remove it from the state array and the game continues to use
	the previous state. We remove the pause state using the resume button's callback */
	TheWindow::WindowInstance()->GetGameStateMachine()->PopState();
}

void PauseState::SetCallbacks(const vector<Callback>& callbacks_)
{
	if (!gameObjects.empty())
	{
		// Loop through all the created game objects
		for (int i = 0; i < gameObjects.size(); i++)
		{
			// If they are of type MenuButton, assign the callback based on the ID passed in the file
			if (dynamic_cast<MenuButton*>(gameObjects[i]))
			{
				MenuButton* menuButton = dynamic_cast<MenuButton*>(gameObjects[i]);

				// Use the object's callbackID as the index into the callbacks vector and assign the correct function
				menuButton->SetCallback(callbacks_[menuButton->GetCallbackID()]);
			}
		}
	}
}
