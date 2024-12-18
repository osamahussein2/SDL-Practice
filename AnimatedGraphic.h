#pragma once

#include "SDLGameObject.h"
#include "InputHandler.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* loaderParams_, int animationSpeed_);

	virtual void Update();

private:
	int animationSpeed;
};