#include "Enemy.h"

Enemy::Enemy(const LoaderParams* loaderParams_) : SDLGameObject(loaderParams_)
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
	x += 1;
	y += 1;

	/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
	the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
	the amount of the animation frames in the sprite sheet */
	currentFrame = static_cast<int>((SDL_GetTicks() / 100) % 6);
}

void Enemy::Clean()
{

}