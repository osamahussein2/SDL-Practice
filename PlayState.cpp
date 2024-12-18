#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "PauseState.h"
#include "GameOverState.h"

const string PlayState::playID = "PLAY";

typedef InputHandler TheInputHandler;
typedef TextureManager TheTextureManager;
typedef Window TheWindow;

void PlayState::Update()
{
	if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		// Push the pause state into the game state when pressing the ESCAPE key
		// PushState doesn't remove the old state but merely stops using it and uses the new state
		TheWindow::WindowInstance()->GetGameStateMachine()->PushState(new PauseState());
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}

	// We have to use a dynamic cast object to cast our GameObject* class to an SDLGameObject* class
	if (CheckCollision(dynamic_cast<SDLGameObject*>(gameObjects[0]), dynamic_cast<SDLGameObject*>(gameObjects[1])))
	{
		// If collision does occur, transition to the game over state
		TheWindow::WindowInstance()->GetGameStateMachine()->PushState(new GameOverState());
	}
}

void PlayState::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();
	}
}

bool PlayState::OnEnter()
{
	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Helicopter.png", "Helicopter",
		TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Helicopter2.png", "Helicopter2",
		TheWindow::WindowInstance()->GetRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(new LoaderParams(500, 100, 128, 55, "Helicopter"));
	GameObject* enemy = new Enemy(new LoaderParams(100, 100, 110, 55, "Helicopter2"));

	gameObjects.push_back(player);
	gameObjects.push_back(enemy);

	cout << "entering PlayState" << endl;
	return true;
}

bool PlayState::OnExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Clean();
	}

	gameObjects.clear();
	TheTextureManager::TextureManagerInstance()->ClearFromTextureMap("Helicopter");

	cout << "exiting PlayState" << endl;
	return true;
}

string PlayState::GetStateID() const
{
	return playID;
}

bool PlayState::CheckCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int LeftA, LeftB;
	int RightA, RightB;
	int TopA, TopB;
	int BottomA, BottomB;

	LeftA = p1->GetPosition().GetX();
	RightA = p1->GetPosition().GetX() + p1->GetWidth();
	TopA = p1->GetPosition().GetY();
	BottomA = p1->GetPosition().GetY() + p1->GetHeight();

	LeftB = p2->GetPosition().GetX();
	RightB = p2->GetPosition().GetX() + p2->GetWidth();
	TopB = p2->GetPosition().GetY();
	BottomB = p2->GetPosition().GetY() + p2->GetHeight();

	if (BottomA <= TopB) { return false; }
	if (TopA >= BottomB) { return false; }
	if (RightA <= LeftB) { return false; }
	if (LeftA >= RightB) { return false; }

	return true;
}
