#pragma once

#include <SDL.h>

#include <vector>
#include <iostream>

#include "Window.h"
#include "Vector2.h"

// SDL supports various types of UI (user interface) devices like joysticks, gamepads, mouse and keyboard

using namespace std;

enum MouseButtons
{
	LEFT_MOUSE_BUTTON = 0,
	MIDDLE_MOUSE_BUTTON = 1,
	RIGHT_MOUSE_BUTTON = 2
};

class InputHandler
{
public:
	static InputHandler* InputHandlerInstance();

	void InitializeJoysticks();
	bool JoysticksInitialized();

	// The joy parameter is the identifier (ID) of the joystick we want to use
	// The stick parameter is for using 1 for left analog stick and 2 for right analog stick
	int xValue(int joy, int stick);
	int yValue(int joy, int stick);

	bool GetJoystickButtonState(int joy, int buttonNumber);
	bool GetMouseButtonState(int buttonNumber);

	Vector2* GetMousePosition();

	bool IsKeyDown(SDL_Scancode key);

	void UpdateInputHandler();
	void CleanInputHandler();

private:
	InputHandler() : joystickInitialized(false), mousePosition(new Vector2(0, 0)), keyPressed(false)
	{
		for (int i = 0; i < 3; i++)
		{
			mouseButtonStates.push_back(false);
		}
	};

	~InputHandler() {};

	// Handle keybaord events
	void OnKeyDown();
	void OnKeyUp();

	// Handle mouse events
	void OnMouseMove(SDL_Event& event);
	void OnMouseButtonDown(SDL_Event& event);
	void OnMouseButtonUp(SDL_Event& event);

	// Handle joystick events
	void OnJoystickAxisMove(SDL_Event& event);
	void OnJoystickButtonDown(SDL_Event& event);
	void OnJoystickButtonUp(SDL_Event& event);

	static InputHandler* inputHandlerInstance;

	bool joystickInitialized;

	/* The value 10000 may seem like a big value to use for stick at rest, but the sensitivity of a controller can be
	very high and so requires a value as large as this */
	const int joystickDeadZone = 10000;

	vector<SDL_Joystick*> joysticks;

	/*
		Specific values for the controller:

		Left and right movement on stick 1 is axis 0
		Up and down movement on stick 1 is axis 1
		Left and right movement on stick 2 is axis 2
		Up and down movement on stick 2 is axis 3

		The Xbox 360 controller uses axes 2 and 5 for the analog triggers
	*/

	/* To handle mutliple controllers with multiple axes, we need a vector of pairs of Vector2, one for each stick */
	vector<pair<Vector2*, Vector2*>> joystickValues;

	// Each controller will have an array of boolean values, one for each button on the controller
	vector<vector<bool>> buttonStates;

	// SDL numbers the mouse buttons as 0 for left, 1 for middle and 2 for right
	vector<bool> mouseButtonStates;

	Vector2* mousePosition;

	const Uint8* keyState;

	bool keyPressed;
};