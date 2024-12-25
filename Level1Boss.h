#pragma once

#include "Enemy.h"
#include "Window.h"

typedef Window TheWindow;

class Level1Boss : public Enemy
{
public:
    virtual ~Level1Boss() {}

    Level1Boss() : Enemy()
    {
        dyingTime = 100;
        health = 100;
        bulletFiringSpeed = 100;
        moveSpeed = 2;

        entered = false;
    }

    virtual void LoadGameObject(std::unique_ptr<LoaderParams> const& loaderParams_)
    {
        ShooterObject::LoadGameObject(std::move(loaderParams_));

        velocity.SetY(-moveSpeed);
    }

    virtual void Collision()
    {
        if (entered)
        {
            health -= 1;

            if (health == 0)
            {
                if (!playedDeathSound)
                {
                    position.SetX(position.GetX() + 30);
                    position.SetY(position.GetY() + 70);
                    TheSoundManager::Instance()->playSound("explode", 0);

                    textureID = "bossexplosion";
                    currentFrame = 0;
                    numberOfFrames = 9;
                    width = 180;
                    height = 180;
                    isDying = true;
                }

            }
        }
    }

    virtual void Update()
    {
        if (!entered)
        {
            Scroll(TheWindow::WindowInstance()->GetScrollSpeed());

            if (position.GetX() < (TheWindow::WindowInstance()->GetWindowWidth() - (width + 20)))
            {
                entered = true;
            }
        }
        else
        {
            if (!isDying)
            {
                if (position.GetY() + height >= TheWindow::WindowInstance()->GetWindowHeight())
                {
                    velocity.SetY(-moveSpeed);
                }
                else if (position.GetY() <= 0)
                {
                    velocity.SetY(moveSpeed);
                }

                if (bulletCounter == bulletFiringSpeed)
                {
                    TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY() + 15, 16, 16,
                        "bullet2", 1, Vector2(-10, 0));
                    TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY() + 25, 16, 16,
                        "bullet2", 1, Vector2(-10, 0));

                    TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY() + 200, 16, 16,
                        "bullet2", 1, Vector2(-10, 0));
                    TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY() + 215, 16, 16,
                        "bullet2", 1, Vector2(-10, 0));

                    bulletCounter = 0;
                }

                bulletCounter++;

                ShooterObject::Update();
            }

            else
            {
                Scroll(TheWindow::WindowInstance()->GetScrollSpeed());
                currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % numberOfFrames));

                if (dyingCounter == dyingTime)
                {
                    isDead = true;
                    TheWindow::WindowInstance()->SetLevelComplete(true);
                }
                
                dyingCounter++;
            }
        }
    }

private:
    bool entered;
};

class Level1BossCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Level1Boss();
    }
};