#pragma once

#include <SDL.h>
#include "GameObject.h"

class PlatformerObject : public GameObject
{
public:
	virtual ~PlatformerObject() {}

	virtual void Draw();
	virtual void Update();
	virtual void Clean() {}

	virtual void Collision() {}
	virtual string Type() { return "PlatformerObject"; }

	virtual void LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_);

protected:
	PlatformerObject();

	bool CheckCollideTile(Vector2 newPos_);

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

	bool flipped;

	bool moveLeft;
	bool moveRight;
	bool isRunning;
	bool isFalling;
	bool isJumping;
	bool canJump;

	Vector2 lastSafePosition;
	int jumpHeight;
};