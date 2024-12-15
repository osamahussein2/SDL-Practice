#include "Player.h"

Player::Player(const LoaderParams* loaderParams_) : SDLGameObject(loaderParams_)
{

}

void Player::Draw()
{
	/* The :: operator is called the scope resolution operator and it is used to identify the specific place that some
	data or function resides */
	SDLGameObject::Draw();
}

void Player::Update()
{
	// A derived class can override the functionality of a parent class
	x -= 1;

	/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
	the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
	the amount of the animation frames in the sprite sheet */
	currentFrame = static_cast<int>((SDL_GetTicks() / 100) % 6);
}

void Player::Clean()
{

}