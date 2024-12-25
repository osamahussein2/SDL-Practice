#pragma once

#include <iostream>
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include <math.h>
#include "Enemy.h"

class Glider : public Enemy
{
public:
    Glider() : Enemy()
    {
        dyingTime = 25;
        health = 1;
        moveSpeed = 3;
        gap = 60;
    }

    virtual ~Glider() {}

    virtual void LoadGameObject(std::unique_ptr<LoaderParams> const& loaderParams_)
    {
        ShooterObject::LoadGameObject(std::move(loaderParams_));

        velocity.SetX(-moveSpeed);
        velocity.SetY(moveSpeed / 2);

        maxHeight = position.GetY() + gap;
        minHeight = position.GetY() - gap;
    }

    virtual void Collision()
    {
        health -= 1;

        if (health == 0)
        {
            if (!playedDeathSound)
            {
                TheSoundManager::Instance()->playSound("explode", 0);

                textureID = "explosion";
                currentFrame = 0;
                numberOfFrames = 9;
                width = 40;
                height = 40;
                isDying = true;
            }

        }
    }

    virtual void Update()
    {
        if (!isDying)
        {
            if (position.GetY() >= maxHeight)
            {
                velocity.SetY(-moveSpeed);
            }
            else if (position.GetY() <= minHeight)
            {
                velocity.SetY(moveSpeed);
            }

        }

        else
        {
            velocity.SetX(0);
            velocity.SetY(0);
            DoDyingAnimation();
        }

        ShooterObject::Update();
    }

private:
    int minHeight, maxHeight, gap;
};

class GliderCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Glider();
    }
};