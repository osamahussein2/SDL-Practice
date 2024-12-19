#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{
}

void AnimatedGraphic::Draw()
{
	SDLGameObject::Draw();
}

void AnimatedGraphic::Update()
{
	/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
	the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
	the amount of the animation frames in the sprite sheet */
	currentFrame = (int)(((SDL_GetTicks() / (1000 / animationSpeed)) % 2));
}

void AnimatedGraphic::Clean()
{
}

void AnimatedGraphic::LoadGameObject(const LoaderParams* loaderParams_)
{
	SDLGameObject::LoadGameObject(loaderParams_);

	animationSpeed = loaderParams_->GetAnimationSpeed();
}
