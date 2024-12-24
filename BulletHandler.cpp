#include "BulletHandler.h"
#include "Window.h"

typedef Window TheWindow;

BulletHandler* BulletHandler::bulletHandlerInstance = 0;

void BulletHandler::AddPlayerBullet(int x_, int y_, int width_, int height_, string textureID_, int numberOfFrames_, Vector2 heading_)
{
	PlayerBullet* playerBullet = new PlayerBullet();

	playerBullet->LoadGameObject(unique_ptr<LoaderParams>(new LoaderParams(x_, y_, width_, height_, textureID_, 
		numberOfFrames_)), heading_);

	playerBullets.push_back(playerBullet);
}

void BulletHandler::AddEnemyBullet(int x_, int y_, int width_, int height_, string textureID_, int numberOfFrames_, Vector2 heading_)
{
	EnemyBullet* enemyBullet = new EnemyBullet();

	enemyBullet->LoadGameObject(unique_ptr<LoaderParams>(new LoaderParams(x_, y_, width_, height_, textureID_,
		numberOfFrames_)), heading_);

	enemyBullets.push_back(enemyBullet);
}

void BulletHandler::UpdateBullets()
{
	// Destroy any bullets that have gone off the screen
	for (vector<PlayerBullet*>::iterator p_it = playerBullets.begin(); p_it != playerBullets.end();)
	{
		// If the player's bullets go offscreen or has died
		if ((*p_it)->GetPosition().GetX() < 0 || (*p_it)->GetPosition().GetX() > TheWindow::WindowInstance()->GetWindowWidth()
			|| (*p_it)->GetPosition().GetY() < 0 || (*p_it)->GetPosition().GetY() > TheWindow::WindowInstance()->GetWindowHeight()
			|| (*p_it)->IsDead())
		{
			delete* p_it; // Delete the bullet
			p_it = playerBullets.erase(p_it); // Remove it from the array
		}

		// Continue to update bullet and loop
		else
		{
			(*p_it)->Update();
			++p_it;
		}
	}

	for (vector<EnemyBullet*>::iterator it = enemyBullets.begin(); it != enemyBullets.end();)
	{
		// If the player's bullets go offscreen or has died
		if ((*it)->GetPosition().GetX() < 0 || (*it)->GetPosition().GetX() > TheWindow::WindowInstance()->GetWindowWidth()
			|| (*it)->GetPosition().GetY() < 0 || (*it)->GetPosition().GetY() > TheWindow::WindowInstance()->GetWindowHeight()
			|| (*it)->IsDead())
		{
			delete* it; // Delete the bullet
			it = enemyBullets.erase(it); // Remove it from the array
		}

		// Continue to update bullet and loop
		else
		{
			(*it)->Update();
			++it;
		}
	}
}

void BulletHandler::DrawBullets()
{
	for (int i = 0; i < playerBullets.size(); i++)
	{
		playerBullets[i]->Draw();
	}

	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Draw();
	}
}

void BulletHandler::ClearBullets()
{
	enemyBullets.clear();
	playerBullets.clear();
}
