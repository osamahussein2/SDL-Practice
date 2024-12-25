#pragma once

#include <iostream>
#include <vector>
#include "PlatformerObject.h"
#include "GameObjectFactory.h"

class Player : public PlatformerObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_);

	virtual void Collision();

	virtual string Type() { return "Player"; }

private:

	// Bring the player back if there are lives left
	void Ressurect();

	// Handle any input from the keyboard, mouse, or joystick
	void HandleInput();

	// Handle any animation for the player
	void HandleAnimation();

	void HandleMovement(Vector2 velocity_);

	// Player can be invulnerable for a time
	int invulnerable, invulnerableTime, invulnerableCounter;

	bool pressedJump;
};

class PlayerCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new Player();
	}
};