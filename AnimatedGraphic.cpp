#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : PlatformerObject()
{
}

void AnimatedGraphic::Draw()
{
	PlatformerObject::Draw();
}

void AnimatedGraphic::Update()
{
	/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
	the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
	the amount of the animation frames in the sprite sheet */
	currentFrame = (int)(((SDL_GetTicks() / (1000 / animationSpeed)) % numberOfFrames));
}

void AnimatedGraphic::Clean()
{
	PlatformerObject::Clean();
}

void AnimatedGraphic::LoadGameObject(unique_ptr<LoaderParams> const& loaderParams_)
{
	PlatformerObject::LoadGameObject(loaderParams_);

	animationSpeed = loaderParams_->GetAnimationSpeed();
}
