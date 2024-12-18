#include "MenuState.h"
#include "MenuButton.h"
#include "PlayState.h"

const string MenuState::menuID = "MENU";

typedef TextureManager TheTextureManager;
typedef Window TheWindow;

void MenuState::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

void MenuState::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();
	}
}

bool MenuState::OnEnter()
{
	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Buttons/Play button sheet.png", "PlayButton",
		TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Buttons/Exit button sheet.png", "ExitButton",
		TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	GameObject* playButton = new MenuButton(new LoaderParams(225, 100, 166, 100, "PlayButton"), MenuToPlay);
	GameObject* exitButton = new MenuButton(new LoaderParams(225, 300, 166, 100, "ExitButton"), ExitFromMenu);

	gameObjects.push_back(playButton);
	gameObjects.push_back(exitButton);

	cout << "entering MenuState" << endl;
	return true;
}

bool MenuState::OnExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Clean();
	}

	gameObjects.clear();
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("PlayButton");
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("ExitButton");

	cout << "exiting MenuState" << endl;
	return true;
}

string MenuState::GetStateID() const
{
	return menuID;
}

void MenuState::MenuToPlay()
{
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new PlayState());
}

void MenuState::ExitFromMenu()
{
	TheWindow::WindowInstance()->isRunning = false;
}
