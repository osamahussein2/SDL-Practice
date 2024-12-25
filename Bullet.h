#pragma once

//#include "PlatformerObject.h"
//#include "TextureManager.h"
//#include "Window.h"
//#include <iostream>

/*class PlayerBullet : public PlatformerObject
{
public:
	PlayerBullet() : PlatformerObject(), heading(0, 0)
	{
		dyingTime = 5;
	}

	virtual ~PlayerBullet() {}

	virtual string Type() { return "PlayerBullet"; }

	virtual void LoadGameObject(unique_ptr<LoaderParams> const& loaderParams_, Vector2 heading_)
	{
		PlatformerObject::LoadGameObject(move(loaderParams_));

		heading = heading_;
	}

	virtual void Draw()
	{
		PlatformerObject::Draw();
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

			PlatformerObject::Update();
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
		PlatformerObject::Clean();
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
}; */