#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : ShooterObject()
{
}

void AnimatedGraphic::Draw()
{
	ShooterObject::Draw();
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

void AnimatedGraphic::LoadGameObject(unique_ptr<LoaderParams> const& loaderParams_)
{
	ShooterObject::LoadGameObject(loaderParams_);

	animationSpeed = loaderParams_->GetAnimationSpeed();
}
