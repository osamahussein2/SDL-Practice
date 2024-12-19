#include "GameOverState.h"
#include "PlayState.h"
#include "StateParser.h"

const string GameOverState::gameOverID = "GAMEOVER";

typedef InputHandler TheInputHandler;
typedef TextureManager TheTextureManager;
typedef Window TheWindow;

void GameOverState::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

void GameOverState::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();
	}
}

bool GameOverState::OnEnter()
{
	StateParser stateParser;

	// Parse the current state along with the XML file
	stateParser.ParseState("test.xml", gameOverID, &gameObjects, &textureIDList);

	// Push callbacks into the array inherited from MenuState

	callbacks.push_back(0); // Push back 0 since callbackID start from 1
	callbacks.push_back(GameOverToMain);
	callbacks.push_back(RestartPlay);

	// Set the callbacks for menu items
	SetCallbacks(callbacks);

	cout << "entering GameOverState" << endl;
	return true;
}

bool GameOverState::OnExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Clean();
	}

	gameObjects.clear();

	GameState::ClearTextures();

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
			menuButton->SetCallback(callbacks[menuButton->GetCallbackID()]);
		}
	}
}
