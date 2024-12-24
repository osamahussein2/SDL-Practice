#pragma once

#include "ShooterObject.h"
#include "TextureManager.h"
#include "Window.h"
#include <iostream>

class PlayerBullet : public ShooterObject
{
public:
	PlayerBullet() : ShooterObject(), heading(0, 0)
	{
		dyingTime = 5;
	}

	virtual ~PlayerBullet() {}

	virtual string Type() { return "PlayerBullet"; }

	virtual void LoadGameObject(unique_ptr<LoaderParams> const& loaderParams_, Vector2 heading_)
	{
		ShooterObject::LoadGameObject(move(loaderParams_));

		heading = heading_;
	}

	virtual void Draw()
	{
		ShooterObject::Draw();
	}

	virtual void Collision()
	{
		textureID = "smallexplosion";
		currentFrame = 0;
		numberOfFrames = 2;
		width = 20;
		height = 20;
		isDying = true;
	}

	virtual void Update()
	{
		if (!isDying)
		{
			velocity.SetX(heading.GetX());
			velocity.SetY(heading.GetY());

			ShooterObject::Update();
		}

		else
		{
			velocity.SetX(0);
			velocity.SetY(0);

			DoDyingAnimation();
		}
	}

	virtual void Clean()
	{
		ShooterObject::Clean();
	}

private:
	Vector2 heading;
};

// Enemy bullet class
class EnemyBullet : public PlayerBullet
{
public:
	EnemyBullet() : PlayerBullet() 
	{
	}

	virtual ~EnemyBullet() {}

	virtual string Type() { return "EnemyBullet"; }
};