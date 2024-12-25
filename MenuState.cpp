#include "MenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"

const string MainMenuState::menuID = "MENU";

typedef InputHandler TheInputHandler;

void MainMenuState::Update()
{
	if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		MenuToPlay();
	}

	if (!gameObjects.empty())
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (gameObjects[i] != 0)
			{
				gameObjects[i]->Update();
			}
		}
	}

	/*for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}*/
}

void MainMenuState::Render()
{
	if (loadingComplete && !gameObjects.empty())
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Draw();
		}
	}
}

bool MainMenuState::OnEnter()
{
	StateParser stateParser;

	// Parse the current state along with the XML file
	stateParser.ParseState("Attack.xml", menuID, &gameObjects, &textureIDList);

	// Push callbacks into the array inherited from MenuState

	callbacks.push_back(0); // Push back 0 since callbackID start from 1
	callbacks.push_back(MenuToPlay);
	callbacks.push_back(ExitFromMenu);

	// Set the callbacks for menu items
	SetCallbacks(callbacks);

	loadingComplete = true;

	cout << "entering MenuState" << endl;
	return true;
}

bool MainMenuState::OnExit()
{
	exiting = true;

	if (loadingComplete && !gameObjects.empty())
	{
		gameObjects.back()->Clean();
		gameObjects.pop_back();
	}

	gameObjects.clear();

	GameState::ClearTextures();
	
	TheInputHandler::InputHandlerInstance()->Reset();

	cout << "exiting MenuState" << endl;
	return true;
}

string MainMenuState::GetStateID() const
{
	return menuID;
}

void MainMenuState::SetCallbacks(const vector<Callback>& callbacks_)
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

void MainMenuState::MenuToPlay()
{
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new PlayState());
}

void MainMenuState::ExitFromMenu()
{
	TheWindow::WindowInstance()->isRunning = false;
}
