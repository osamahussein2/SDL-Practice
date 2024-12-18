#include "GameOverState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"

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
	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Animated Text/Game Over text sheet.png",
		"GameOverText", TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Buttons/Main Menu button sheet.png",
		"MainMenu", TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Buttons/Restart button sheet.png",
		"RestartGame", TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}
	
	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 225, 35, "GameOverText"), 2);
	GameObject* mainMenuButton = new MenuButton(new LoaderParams(200, 200, 153, 80, "MainMenu"), GameOverToMain);
	GameObject* restartButton = new MenuButton(new LoaderParams(200, 300, 160, 80, "RestartGame"), RestartPlay);

	gameObjects.push_back(gameOverText);
	gameObjects.push_back(mainMenuButton);
	gameObjects.push_back(restartButton);

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
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("GameOverText");
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("MainMenu");
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("RestartGame");

	cout << "exiting GameOverState" << endl;
	return true;
}

string GameOverState::GetStateID() const
{
	return gameOverID;
}

void GameOverState::GameOverToMain()
{
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new MenuState());
}

void GameOverState::RestartPlay()
{
	TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new PlayState());
}
