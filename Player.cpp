#include "Player.h"
#include "Window.h"
#include "InputHandler.h"
#include "TileLayer.h"
#include "BulletHandler.h"
#include "SoundManager.h"

typedef InputHandler TheInputHandler;

Player::Player() : ShooterObject(), invulnerable(false), invulnerableTime(200), invulnerableCounter(0)
{

}

void Player::Collision()
{
	// if the player is not invulnerable then set to dying and change values for death animation tile sheet
	if (!invulnerable && !TheWindow::WindowInstance()->GetLevelComplete())
	{
		textureID = "largeexplosion";
		currentFrame = 0;
		numberOfFrames = 9;
		width = 60;
		height = 60;
		isDying = true;
	}
}

void Player::LoadGameObject(unique_ptr<LoaderParams> const& loaderParams_)
{
	ShooterObject::LoadGameObject(move(loaderParams_));

	// set up bullets
	bulletFiringSpeed = 13;
	moveSpeed = 3;

	// we want to be able to fire instantly
	bulletCounter = bulletFiringSpeed;

	// time it takes for death explosion
	dyingTime = 100;
}

void Player::Draw()
{
	/* The :: operator is called the scope resolution operator and it is used to identify the specific place that some
	data or function resides */
	ShooterObject::Draw();
}

void Player::Update()
{
	// A derived class can override the functionality of a parent class

	// If the level is complete, then fly off the screen
	if (TheWindow::WindowInstance()->GetLevelComplete())
	{
		/* Once a level is complete and the player has flown offscreen, increment the current level */
		if (position.GetX() >= TheWindow::WindowInstance()->GetWindowWidth())
		{
			TheWindow::WindowInstance()->SetCurrentLevel(TheWindow::WindowInstance()->GetCurrentLevel() + 1);
		}

		else
		{
			velocity.SetX(3);
			velocity.SetY(0);
			ShooterObject::Update();
			HandleAnimation();
		}
	}

	else
	{
		// If the player isn't doing the death animation, then update it normally
		if (!isDying)
		{
			// Reset velocity
			velocity.SetX(0);
			velocity.SetY(0);

			// Get input
			HandleInput();

			// Do normal position += velocity update
			ShooterObject::Update();

			// Update the animation
			HandleAnimation();
		}

		// If the player is doing the death animation though
		else
		{
			/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
			the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
			the amount of the animation frames in the sprite sheet */
			currentFrame = static_cast<int>((SDL_GetTicks() / 100) % numberOfFrames);

			// If the death animation has completed
			if (dyingCounter == dyingTime)
			{
				// Ressurect the player
				Ressurect();
			}

			dyingCounter++;
		}
	}
}

void Player::Clean()
{
	ShooterObject::Clean();
}

void Player::Ressurect()
{
	/* The Ressurect function resets the player back to the center of the screen and temporarily makes the Player object
	invulnerable, which is visualized using alpha of the texture. This function is also responsible for resetting the size
	value of the texture which is changed in DoDyingAnimation to accommodate for the explosion texture */

	TheWindow::WindowInstance()->SetPlayerLives(TheWindow::WindowInstance()->GetPlayerLives() - 1);

	position.SetX(10);
	position.SetY(200);

	isDying = false;

	textureID = "player";

	currentFrame = 0;
	numberOfFrames = 5;
	width = 101;
	height = 46;

	dyingCounter = 0;
	invulnerable = true;
}

void Player::HandleInput()
{
	if (!isDead)
	{
		// handle keys
		if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_UP) && position.GetY() > 0)
		{
			velocity.SetY(-moveSpeed);
		}
		else if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_DOWN) && (position.GetY() + height) < 
			TheWindow::WindowInstance()->GetWindowHeight() - 10)
		{
			velocity.SetY(moveSpeed);
		}

		if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_LEFT) && position.GetX() > 0)
		{
			velocity.SetX(-moveSpeed);
		}
		else if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_RIGHT) && (position.GetX() + width) <
			TheWindow::WindowInstance()->GetWindowWidth())
		{
			velocity.SetX(moveSpeed);
		}

		if (TheInputHandler::InputHandlerInstance()->IsKeyDown(SDL_SCANCODE_SPACE))
		{
			if (bulletCounter == bulletFiringSpeed)
			{
				TheSoundManager::Instance()->playSound("shoot", 0);
				TheBulletHandler::Instance()->AddPlayerBullet(position.GetX() + 90, position.GetY() + 12, 11, 11,
					"bullet1", 1, Vector2(10, 0));
				bulletCounter = 0;
			}

			bulletCounter++;
		}

		else
		{
			bulletCounter = bulletFiringSpeed;
		}
	}

	/*Vector2* target = TheInputHandler::InputHandlerInstance()->GetMousePosition();

	velocity = *target - position;

	velocity /= 50;*/

	/*if (TheInputHandler::InputHandlerInstance()->JoysticksInitialized())
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
	}*/

	//Vector2* vec = TheInputHandler::InputHandlerInstance()->GetMousePosition();

	/* Set the velocity from the player's current position to the mouse position by subtracting the desired location from
	the current location (mouse motion) */

	// Divide the vector by 100 to see objects following the mouse as opposed to sticking to the mouse position
	//velocity = (*vec - position) / 100;
}

void Player::HandleAnimation()
{
	/* Animation is a big part of the feel of the Player object; from flashing (when invulnerable), to rotating(when moving
	in a forward or backward direction) */

	// If the player is invulnerable we can flash its alpha to let people know
	if (invulnerable)
	{
		// Invulnerability is finished, reset the values back to default
		if (invulnerableCounter == invulnerableTime)
		{
			invulnerable = false;
			invulnerableCounter = 0;
			alpha = 255;
		}

		// Else, flash the alpha on and off by adjusting the alpha numbers
		else
		{
			if (alpha == 255)
			{
				alpha = 0;
			}

			else
			{
				alpha = 255;
			}
		}

		// Increment the invulnerable counter
		invulnerableCounter++;
	}

	// If the player isn't dead, then we can change the angle with the velocity to give the impression of a moving helicopter
	if (!isDead)
	{
		if (velocity.GetX() < 0)
		{
			angle = -10.0;
		}

		else if (velocity.GetX() > 0)
		{
			angle = 10.0;
		}

		else
		{
			angle = 0.0;
		}
	}

	// Set the current frame to animate the helicopter propellors
	currentFrame = int(((SDL_GetTicks() / (100)) % numberOfFrames));
}
