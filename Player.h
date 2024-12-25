#pragma once

#include <iostream>
#include <vector>
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
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

	// Player can be invulnerable for a time
	int invulnerable, invulnerableTime, invulnerableCounter;
};

class PlayerCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new Player();
	}
};