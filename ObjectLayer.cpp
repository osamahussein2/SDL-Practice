#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Window.h"
#include "Camera.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
	for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		delete (*it);
	}

	gameObjects.clear();
}

void ObjectLayer::Update(Level* level_)
{
    //collisionManager.CheckPlayerEnemyBulletCollision(level_->GetPlayer());
    //collisionManager.CheckEnemyPlayerBulletCollision((const vector<GameObject*>&) gameObjects);
    collisionManager.CheckPlayerEnemyCollision(level_->GetPlayer(), (const vector<GameObject*>&) gameObjects);

    /*if (level_->GetPlayer()->GetPosition().GetX() + level_->GetPlayer()->GetWidth() <
        TheWindow::WindowInstance()->GetWindowWidth())
    {
        collisionManager.CheckPlayerTileCollision(level_->GetPlayer(), level_->GetCollidableLayers());
    }*/

    // Iterate through the objects
    if (!gameObjects.empty())
    {
        for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();)
        {
            if ((*it)->GetPosition().GetX() <= TheCamera::CameraInstance()->GetPosition().x + 
                TheWindow::WindowInstance()->GetWindowWidth())
            {
                (*it)->SetUpdating(true);
                (*it)->Update();
            }
            else
            {
                if ((*it)->Type() != string("Player"))
                {
                    (*it)->SetUpdating(false);
                    (*it)->Scroll(TheWindow::WindowInstance()->GetScrollSpeed());
                }
                else
                {
                    (*it)->Update();
                }
            }

            // Check if dead or off screen
            if ((*it)->IsDead() || (*it)->GetPosition().y > TheWindow::WindowInstance()->GetWindowHeight())
            {
                delete* it;
                it = gameObjects.erase(it); // Erase from vector and get new iterator
            }
            else
            {
                ++it; // Increment if everything works
            }

        }
    }
}

void ObjectLayer::Render()
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Draw();
    }
}

vector<GameObject*>* ObjectLayer::GetGameObjects()
{
	return &gameObjects;
}
