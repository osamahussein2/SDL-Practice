#pragma once

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{
public:
	virtual string Type() { return "Enemy"; }

protected:
	Enemy() : ShooterObject() {}
	virtual ~Enemy() {}

	int health;
};