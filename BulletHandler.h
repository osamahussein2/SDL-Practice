#pragma once

/*#include <iostream>
#include <vector>
#include "Bullet.h"

using namespace std;

class BulletHandler
{
public:
	static BulletHandler* Instance()
	{
		if (bulletHandlerInstance == 0)
		{
			bulletHandlerInstance = new BulletHandler();
			return bulletHandlerInstance;
		}

		return bulletHandlerInstance;
	}

	void AddPlayerBullet(int x_, int y_, int width_, int height_, string textureID_, int numberOfFrames_, Vector2 heading_);
	void AddEnemyBullet(int x_, int y_, int width_, int height_, string textureID_, int numberOfFrames_, Vector2 heading_);

	void UpdateBullets();
	void DrawBullets();
	void ClearBullets();


	const vector<PlayerBullet*> GetPlayerBullets() { return playerBullets; }
	const vector<EnemyBullet*> GetEnemyBullets() { return enemyBullets; }

private:
	BulletHandler();
	~BulletHandler();

	BulletHandler(const BulletHandler&);
	BulletHandler& operator=(const BulletHandler&);

	static BulletHandler* bulletHandlerInstance;

	vector<PlayerBullet*> playerBullets;
	vector<EnemyBullet*> enemyBullets;
};

typedef BulletHandler TheBulletHandler;*/