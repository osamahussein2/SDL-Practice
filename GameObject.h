#pragma once

#include <string>
#include <memory>
#include "LoaderParams.h"
#include "Vector2.h"

class GameObject
{
public:

	/* Polymorphism allows us to refer to an object through a pointer to its parent or base class. This will allow us 
	to essentially make our Game class only need to store a list of pointers to one type and any derived types can
	also be added to this list. */

	/* Virtual keyword means that when calling this function through a pointer, it uses the definition from the type 
	of the object itself, not the type of its pointer */

	/* Pure virtual functions force any derived classes to also declare and implement them */

	virtual ~GameObject() {}

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;

	// std::unique_ptr is a part of the new C++11 standard and ensures that the pointer is deleted after going out of scope
	virtual void LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_) = 0;

	// Handle collisions accordingly if the object has collided with another object
	virtual void Collision() = 0;

	// Get the type of the object
	virtual string Type() = 0;

	Vector2& GetPosition() { return position; }
	Vector2& GetVelocity() { return velocity; }

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void Scroll(float scrollSpeed_) 
	{ 
		if (Type() != string("Player"))
		{
			position.SetX(position.GetX() - scrollSpeed_);
		}
	}

	bool Updating() { return isUpdating; }
	bool IsDead() { return isDead; }
	bool IsDying() { return isDying; }

	void SetUpdating(bool isUpdating_) { isUpdating = isUpdating_; }

protected:
	GameObject() : position(0, 0), velocity(0, 0), acceleration(0, 0), width(0), height(0), currentRow(0), currentFrame(0),
	isUpdating(false), isDead(false), isDying(false), angle(0), alpha(255) {}

	// Movement variables
	Vector2 position, velocity, acceleration;

	// Size variables
	int width, height;

	// Animation variables
	int currentRow, currentFrame, numberOfFrames;
	string textureID;

	// Game boolean variables
	bool isUpdating, isDead, isDying;

	// Rotation
	double angle;

	// Blending
	int alpha;
};