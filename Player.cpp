#include "Player.h"

typedef InputHandler TheInputHandler;

Player::Player(const LoaderParams* loaderParams_) : SDLGameObject(loaderParams_)
{

}

void Player::Draw()
{
	/* The :: operator is called the scope resolution operator and it is used to identify the specific place that some
	data or function resides */
	SDLGameObject::Draw();
}

void Player::Update()
{
	// A derived class can override the functionality of a parent class
	velocity.SetX(0);
	velocity.SetY(0);

	HandleInput();

	/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
	the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
	the amount of the animation frames in the sprite sheet */
	currentFrame = static_cast<int>((SDL_GetTicks() / 100) % 6);

	SDLGameObject::Update();
}

void Player::Clean()
{

}

void Player::HandleInput()
{
	if (TheInputHandler::InputHandlerInstance()->JoysticksInitialized())
	{
		// Move left/right with the left analog stick
		if (TheInputHandler::InputHandlerInstance()->xValue(0, 1) > 0 ||
			TheInputHandler::InputHandlerInstance()->xValue(0, 1) < 0)
		{
			velocity.SetX(1 * TheInputHandler::InputHandlerInstance()->xValue(0, 1));
		}

		// Move up/down with the left analog stick
		if (TheInputHandler::InputHandlerInstance()->yValue(0, 1) > 0 ||
			TheInputHandler::InputHandlerInstance()->yValue(0, 1) < 0)
		{
			velocity.SetY(1 * TheInputHandler::InputHandlerInstance()->yValue(0, 1));
		}

		// Move left/right with the right analog stick
		if (TheInputHandler::InputHandlerInstance()->xValue(0, 2) > 0 ||
			TheInputHandler::InputHandlerInstance()->xValue(0, 2) < 0)
		{
			velocity.SetX(1 * TheInputHandler::InputHandlerInstance()->xValue(0, 2));
		}

		// Move up/down with the right analog stick
		if (TheInputHandler::InputHandlerInstance()->yValue(0, 2) > 0 ||
			TheInputHandler::InputHandlerInstance()->yValue(0, 2) < 0)
		{
			velocity.SetY(1 * TheInputHandler::InputHandlerInstance()->yValue(0, 2));
		}

		// Set the player's x velocity when pressing the Y button (Yellow button on Xbox controller)
		if (TheInputHandler::InputHandlerInstance()->GetJoystickButtonState(0, 3))
		{
			velocity.SetX(1);
		}
	}

	// Set the player's x velocity when pressing the left mouse button
	if (TheInputHandler::InputHandlerInstance()->GetMouseButtonState(LEFT_MOUSE_BUTTON))
	{
		velocity.SetX(1);
	}

	// Press RIGHT arrow key to move right
	if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		velocity.SetX(2);
	}

	// Press LEFT arrow key to move left
	if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		velocity.SetX(-2);
	}

	// Press UP arrow key to move up
	if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		velocity.SetY(-2);
	}

	// Press DOWN arrow key to move down
	if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		velocity.SetY(2);
	}

	//Vector2* vec = TheInputHandler::InputHandlerInstance()->GetMousePosition();

	/* Set the velocity from the player's current position to the mouse position by subtracting the desired location from
	the current location (mouse motion) */

	// Divide the vector by 100 to see objects following the mouse as opposed to sticking to the mouse position
	//velocity = (*vec - position) / 100;
}
