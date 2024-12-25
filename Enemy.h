#pragma once

#include <iostream>
#include "PlatformerObject.h"

using namespace std;

class Enemy : public PlatformerObject
{
public:
	virtual string Type() { return "Enemy"; }

protected:
	Enemy() : PlatformerObject() {}
	virtual ~Enemy() {}

	int health;
};