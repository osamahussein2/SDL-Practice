#pragma once

#include "LoaderParams.h"

class GameObject
{
public:

	/* Polymorphism allows us to refer to an object through a pointer to its parent or base class. This will allow us 
	to essentially make our Game class only need to store a list of pointers to one type and any derived types can
	also be added to this list. */

	/* Virtual keyword means that when calling this function through a pointer, it uses the definition from the type 
	of the object itself, not the type of its pointer */

	/* Pure virtual functions force any derived classes to also declare and implement them */

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;

protected:
	GameObject(const LoaderParams* loaderParams_) {}
	virtual ~GameObject() {}
};