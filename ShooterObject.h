#pragma once

#include <SDL.h>
#include "GameObject.h"

class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject() {}

	virtual void Draw();
	virtual void Update();
	virtual void Clean() {}

	virtual void Collision() {}
	virtual string Type() { return "ShooterObject"; }

	virtual void LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_);

protected:
	ShooterObject();

	// Draw the animation for the object about to be destroyed
	void DoDyingAnimation();

	// How fast will the object fire bullets with a counter
	int bulletFiringSpeed, bulletCounter;

	// How fast will the object move
	int moveSpeed;

	// How long will the death animation take with a counter
	int dyingTime, dyingCounter;

	// Has the explosion sound played yet?
	bool playedDeathSound;
};