#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "Window.h"
#include "BulletHandler.h"

const string PlayState::playID = "PLAY";

typedef InputHandler TheInputHandler;

void PlayState::Update()
{
	if (loadingComplete && !exiting)
	{
		if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
		{
			// Push the pause state into the game state when pressing the ESCAPE key
			// PushState doesn't remove the old state but merely stops using it and uses the new state
			TheWindow::WindowInstance()->GetGameStateMachine()->PushState(new PauseState());
		}

		//TheBulletHandler::Instance()->UpdateBullets();

		if (TheWindow::WindowInstance()->GetPlayerLives() == 0)
		{
			TheWindow::WindowInstance()->GetGameStateMachine()->ChangeState(new GameOverState());
		}

		if (level != 0)
		{
			level->Update();
		}
	}

	/*for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}*/

	// We have to use a dynamic cast object to cast our GameObject* class to an SDLGameObject* class
	/*if (CheckCollision(dynamic_cast<SDLGameObject*>(gameObjects[0]), dynamic_cast<SDLGameObject*>(gameObjects[1])))
	{
		// If collision does occur, transition to the game over state
		TheWindow::WindowInstance()->GetGameStateMachine()->PushState(new GameOverState());
	}*/
}

void PlayState::Render()
{
	if (loadingComplete)
	{
		if (level != 0)
		{
			level->Render();
		}

		for (int i = 0; i < TheWindow::WindowInstance()->GetPlayerLives(); i++)
		{
			TheTextureManager::TextureManagerInstance()->DrawFrame("lives", i * 30, 0, 32, 30, 0, 0,
				TheWindow::WindowInstance()->GetRenderer(), 0.0, 255, SDL_FLIP_NONE);
		}

		//TheBulletHandler::Instance()->DrawBullets();
	}

	/*for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();
	}*/
}

bool PlayState::OnEnter()
{
	TheWindow::WindowInstance()->SetPlayerLives(3);

	LevelParser levelParser;
	level = levelParser.ParseLevel(TheWindow::WindowInstance()->GetLevelFiles()
		[TheWindow::WindowInstance()->GetCurrentLevel() - 1].c_str());

	TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Bullet1.png", "bullet1", 
		TheWindow::WindowInstance()->GetRenderer());
	TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Bullet2.png", "bullet2", 
		TheWindow::WindowInstance()->GetRenderer());
	TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Bullet3.png", "bullet3", 
		TheWindow::WindowInstance()->GetRenderer());
	TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Lives.png", "lives", 
		TheWindow::WindowInstance()->GetRenderer());

	if (level != 0)
	{
		loadingComplete = true;
	}

	cout << "entering PlayState" << endl;
	return true;
}

bool PlayState::OnExit()
{
	/*for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Clean();
	}

	gameObjects.clear();

	GameState::ClearTextures();*/

	exiting = true;

	TheInputHandler::InputHandlerInstance()->Reset();
	//TheBulletHandler::Instance()->ClearBullets();

	cout << "exiting PlayState" << endl;
	return true;
}

string PlayState::GetStateID() const
{
	return playID;
}
