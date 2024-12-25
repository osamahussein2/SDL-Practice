#pragma once

#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include <math.h>
#include "Enemy.h"

class Turret : public Enemy
{
public:
    Turret()
    {
        dyingTime = 1000;
        health = 15;
        bulletFiringSpeed = 50;
    }

    virtual ~Turret() {}

    virtual void Collision()
    {
        health -= 1;

        if (health == 0)
        {
            if (!playedDeathSound)
            {
                TheSoundManager::Instance()->playSound("explode", 0);

                textureID = "largeexplosion";
                currentFrame = 0;
                numberOfFrames = 9;
                width = 60;
                height = 60;
                isDying = true;
            }

        }
    }

    virtual void Update()
    {
        if (!isDying)
        {
            // Scroll the turret with the rest of the game
            Scroll(TheWindow::WindowInstance()->GetScrollSpeed());

            if (bulletCounter == bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY(), 16, 16, 
                    "bullet2", 1, Vector2(-3, -3));
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX() + 20, position.GetY(), 16, 16, 
                    "bullet2", 1, Vector2(0, -3));
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX() + 40, position.GetY(), 16, 16, 
                    "bullet2", 1, Vector2(3, -3));
                
                bulletCounter = 0;
            }

            bulletCounter++;
        }
        else
        {
            Scroll(TheWindow::WindowInstance()->GetScrollSpeed());
            DoDyingAnimation();
        }
    }
};

class TurretCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new Turret();
	}
};