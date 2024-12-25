#pragma once

/*#include "Glider.h"

class ShotGlider : public Glider
{
public:
	virtual ~ShotGlider() {}

	ShotGlider() : Glider()
	{
		bulletFiringSpeed = 25;
		moveSpeed = 3;
	}

	virtual void LoadGameObject(std::unique_ptr<LoaderParams> const& loaderParams_)
	{
		PlatformerObject::LoadGameObject(std::move(loaderParams_));

		velocity.SetX(-moveSpeed);
	}

    virtual void Update()
    {
        if (!isDying)
        {
            if (bulletCounter == bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY() + 15, 16, 16, 
                    "bullet2", 1, Vector2(-10, 0));
                bulletCounter = 0;
            }

            bulletCounter++;
        }
        else
        {
            velocity.SetX(0);
            DoDyingAnimation();
        }

        PlatformerObject::Update();
    }
};

class ShotGliderCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new ShotGlider();
	}
};*/