#include "InputHandler.h"

/* There are few different structures for handling joystick events in SDL:

	SDL_JoyAxisEvent - Axis motion information (SDL_JOYAXISMOTION)
	SDL_JoyButtonEvent - Button press and release information (SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP)
	SDL_JoyBallEvent - Trackball event motion information (SDL_JOYBALLMOTION)
	SDL_JoyHatEvent - Joystick hat position change (SDL_JOYHATMOTION)
*/

/* SDL consists of mouse events like:

	SDL_MouseButtonEvent - A button on the mouse has been pressed or released (SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP)
	SDL_MouseMotionEvent - The mouse has been moved (SDL_MOUSEMOTION)
	SDL_MouseWheelEvent - The mouse wheel has moved (SDL_MOUSEWHEEL)

*/

InputHandler* InputHandler::inputHandlerInstance = 0;

InputHandler* InputHandler::InputHandlerInstance()
{
	if (inputHandlerInstance == 0)
	{
		inputHandlerInstance = new InputHandler();
	}

	return inputHandlerInstance;
}

void InputHandler::InitializeJoysticks()
{
	// Check whether the joystick sybsystem has been initialized using SDLWasInit
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		// If it's not initialized, then initialize joystick using SDL_InitSubSystem
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	

	// Before trying to open the objects, we use SDL_NumJoysticks to make sure there are some joysticks available
	if (SDL_NumJoysticks() > 0)
	{
		// Loop through the number of joysticks, opening them using SDL_JoystickOpen
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (joy)
			{
				// Push the joystick object into the array for closing later
				joysticks.push_back(joy);

				// We use the Vector2 values to set whether a stick has moved up, down, left, or right
				// When we initialize our joysticks we need to create a pair of Vector2* in the joystickValues array
				joystickValues.push_back(make_pair(new Vector2(0, 0), new Vector2(0, 0)));

				vector<bool> tempButtons;

				// Loop through the joysticks to get the number of these buttons 
				for (int j = 0; i < SDL_JoystickNumButtons(joy); j++)
				{
					// Return the vector to false since no buttons have been pressed
					tempButtons.push_back(false);
				}

				// Push the button states inside the temp buttons array to be used with the GetButtonState function
				buttonStates.push_back(tempButtons);
			}

			else
			{
				cout << SDL_GetError();
			}
		}

		// Tell SDL to listen to joystick events
		SDL_JoystickEventState(SDL_ENABLE);

		// Set joystick initialized to true upon detecting joystick(s)
		joystickInitialized = true;

		cout << "Initialized " << joysticks.size() << " joystick(s)";
	}

	else
	{
		// Else if we don't have a joystick, set joystick initialized to false
		joystickInitialized = false;

		cout << "Couldn't initialize joystick";
	}
}

bool InputHandler::JoysticksInitialized()
{
	return joystickInitialized;
}

int InputHandler::xValue(int joy, int stick)
{
	if (joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return joystickValues[joy].first->GetX();
		}

		else if (stick == 2)
		{
			return joystickValues[joy].second->GetX();
		}
	}

	return 0;
}

int InputHandler::yValue(int joy, int stick)
{
	if (joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return joystickValues[joy].first->GetY();
		}

		else if (stick == 2)
		{
			return joystickValues[joy].second->GetY();
		}
	}

	return 0;
}

bool InputHandler::GetJoystickButtonState(int joy, int buttonNumber)
{
	// Grab the correct button state to look up the correct button from the correct joystick
	return buttonStates[joy][buttonNumber];
}

bool InputHandler::GetMouseButtonState(int buttonNumber)
{
	// Access the mouse button states enum to return the correct mouse button
	return mouseButtonStates[buttonNumber];
}

Vector2* InputHandler::GetMousePosition()
{
	return mousePosition;
}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
	if (keyState != 0)
	{
		if (keyState[key] == 1)
		{
			keyPressed = true;
		}

		else
		{
			keyPressed = false;
		}
	}

	return keyPressed;
}

void InputHandler::UpdateInputHandler()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_QUIT:
			Window::WindowInstance()->isRunning = false;
			break;
			
		/* Each joystick event will have a which variable stored within it
		Using this will allow us to find out which joystick the event came from */

		// Check the type value
		case SDL_JOYAXISMOTION:
			OnJoystickAxisMove(event);
			break;
		
		case SDL_JOYBUTTONDOWN:
			OnJoystickButtonDown(event);
			break;

		case SDL_JOYBUTTONUP:
			OnJoystickButtonUp(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(event);
			break;
			
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(event);
			break;
			
		case SDL_MOUSEMOTION:
			OnMouseMove(event);
			break;

		case SDL_KEYDOWN:
			OnKeyDown();
			break;

		case SDL_KEYUP:
			OnKeyUp();
			break;

		default:
			break;
		}
	}
}

void InputHandler::CleanInputHandler()
{
	// If joystick was initialized, then we must close the joystick to clean it whenever
	if (joystickInitialized == true)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(joysticks[i]);
		}
	}
}

void InputHandler::OnKeyDown()
{
	keyState = SDL_GetKeyboardState(0);
}

void InputHandler::OnKeyUp()
{
	keyState = SDL_GetKeyboardState(0);
}

void InputHandler::OnMouseMove(SDL_Event& event)
{
	mousePosition->SetX(event.motion.x);
	mousePosition->SetY(event.motion.y);
}

void InputHandler::OnMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT_MOUSE_BUTTON] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE_MOUSE_BUTTON] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT_MOUSE_BUTTON] = true;
	}
}

void InputHandler::OnMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT_MOUSE_BUTTON] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE_MOUSE_BUTTON] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT_MOUSE_BUTTON] = false;
	}
}

void InputHandler::OnJoystickAxisMove(SDL_Event& event)
{
	// Get which controller here
	int whichController = event.jaxis.which;

	// Left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichController].first->SetX(1);
		}

		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichController].first->SetX(-1);
		}

		else
		{
			joystickValues[whichController].first->SetX(0);
		}
	}

	// Left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichController].first->SetY(1);
		}

		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichController].first->SetY(-1);
		}

		else
		{
			joystickValues[whichController].first->SetY(0);
		}
	}

	// Right stick move left or right
	if (event.jaxis.axis == 2)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichController].second->SetX(1);
		}

		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichController].second->SetX(-1);
		}

		else
		{
			joystickValues[whichController].second->SetX(0);
		}
	}

	// Right stick move up or down
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > joystickDeadZone)
		{
			joystickValues[whichController].second->SetY(1);
		}

		else if (event.jaxis.value < -joystickDeadZone)
		{
			joystickValues[whichController].second->SetY(-1);
		}

		else
		{
			joystickValues[whichController].second->SetY(0);
		}
	}
}

void InputHandler::OnJoystickButtonDown(SDL_Event& event)
{
	int whichController = event.jaxis.which;

	/* When a button is pressed we get to know which controller it was pressed on and use this as an index into
	the buttonStates array. Then, we use the button number (event.jbutton.button) to set the correct button to
	true */
	buttonStates[whichController][event.jbutton.button] = true;
}

void InputHandler::OnJoystickButtonUp(SDL_Event& event)
{
	int whichController = event.jaxis.which;

	/* When a button is released we get to know which controller it was pressed on and use this as an index into
	the buttonStates array. Then, we use the button number (event.jbutton.button) to set the correct button to
	false */
	buttonStates[whichController][event.jbutton.button] = false;
}
