#include "Enemy.h"

Enemy::Enemy() : SDLGameObject()
{

}

void Enemy::Draw()
{
	/* The :: operator is called the scope resolution operator and it is used to identify the specific place that some
	data or function resides */
	SDLGameObject::Draw();
}

void Enemy::Update()
{
	//position.SetX(position.GetX() + 1);
	//position.SetY(position.GetY() + 1);

	/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
	the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
	the amount of the animation frames in the sprite sheet */
	currentFrame = static_cast<int>((SDL_GetTicks() / 100) % 5);

	if (position.GetY() < 0)
	{
		velocity.SetY(2);
	}

	else if (position.GetY() > 400)
	{
		velocity.SetY(-2);
	}

	SDLGameObject::Update();
}

void Enemy::Clean()
{

}

void Enemy::LoadGameObject(const LoaderParams* loaderParams_)
{
	SDLGameObject::LoadGameObject(loaderParams_);

	velocity.SetY(2);
	velocity.SetX(0.001);
}
