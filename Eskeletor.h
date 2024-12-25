#pragma once

/*#include "Enemy.h"
#include "SoundManager.h"
#include "Window.h"
#include "BulletHandler.h"

typedef Window TheWindow;

class Eskeletor : public Enemy
{
public:
	virtual ~Eskeletor() {}

	Eskeletor() : Enemy()
	{
		dyingTime = 50;
		health = 3;
		moveSpeed = 3;
		bulletFiringSpeed = 50;
	}

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
            Scroll(TheWindow::WindowInstance()->GetScrollSpeed());
            velocity.SetY(moveSpeed);

            if (bulletCounter == bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY(), 16, 16, 
                    "bullet1", 1, Vector2(-3, 0));
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY(), 16, 16, 
                    "bullet1", 1, Vector2(3, 0));
                bulletCounter = 0;
            }
            bulletCounter++;

        }
        else
        {
            velocity.SetY(0);
            DoDyingAnimation();
        }

        PlatformerObject::Update();
    }
};

class EskeletorCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Eskeletor();
    }
};*/