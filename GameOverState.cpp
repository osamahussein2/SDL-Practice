#include "GameOverState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "MenuButton.h"

const string GameOverState::gameOverID = "GAMEOVER";

typedef InputHandler TheInputHandler;

void GameOverState::Update()
{
	if (loadingComplete && !gameObjects.empty())
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update();
		}
	}
}

void GameOverState::Render()
{
	if (loadingComplete && !gameObjects.empty())
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Draw();
		}
	}
}

bool GameOverState::OnEnter()
{
	StateParser stateParser;

	// Parse the current state along with the XML file
	stateParser.ParseState("Attack.xml", gameOverID, &gameObjects, &textureIDList);

	// Push callbacks into the array inherited from MenuState

	callbacks.push_back(0); // Push back 0 since callbackID start from 1
	callbacks.push_back(GameOverToMain);
	callbacks.push_back(RestartPlay);

	loadingComplete = true;

	// Set the callbacks for menu items
	SetCallbacks(callbacks);

	cout << "entering GameOverState" << endl;
	return true;
}

bool GameOverState::OnExit()
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

	cout << "exiting GameOverState" << endl;
	return true;
}

string GameOverState::GetStateID() const
{
	return gameOverID;
}

void GameOverState::GameOverToMain()
{
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new MainMenuState());
}

void GameOverState::RestartPlay()
{
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new PlayState());
}

void GameOverState::SetCallbacks(const vector<Callback>& callbacks_)
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
