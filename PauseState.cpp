#include "PauseState.h"
#include "MenuButton.h"
#include "MenuState.h"

const string PauseState::pauseID = "PAUSE";

typedef InputHandler TheInputHandler;
typedef TextureManager TheTextureManager;
typedef Window TheWindow;

void PauseState::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

void PauseState::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();
	}
}

bool PauseState::OnEnter()
{
	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Buttons/Resume button sheet.png", "ResumeGame",
		TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Buttons/Main Menu button sheet.png", "MainMenu",
		TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	GameObject* mainMenuButton = new MenuButton(new LoaderParams(200, 100, 150, 80, "MainMenu"), PauseToMain);
	GameObject* resumeButton = new MenuButton(new LoaderParams(200, 300, 150, 80, "ResumeGame"), ResumePlay);

	gameObjects.push_back(mainMenuButton);
	gameObjects.push_back(resumeButton);

	cout << "entering PauseState" << endl;
	return true;
}

bool PauseState::OnExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Clean();
	}

	gameObjects.clear();
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("MainMenu");
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("ResumeGame");
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
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new MenuState());
}

void PauseState::ResumePlay()
{
	/* Once we are done with the pushed state, we remove it from the state array and the game continues to use
	the previous state. We remove the pause state using the resume button's callback */
	TheWindow::WindowInstance()->GetGameStateMachine()->PopState();
}
