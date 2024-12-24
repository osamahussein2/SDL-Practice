#include "MenuButton.h"

typedef InputHandler TheInputHandler;

MenuButton::MenuButton() : ShooterObject(), callbackFunction(0), released(true)
{
	// Start at frame 0
	currentFrame = MOUSE_OUT;
}

void MenuButton::Draw()
{
	ShooterObject::Draw();
}

void MenuButton::Update()
{
	Vector2* mousePos = TheInputHandler::InputHandlerInstance()->GetMousePosition();

	/* Check whether the mouse position is less than the position of the right-hand side of the button (x position + width).
	We then check if the mouse position is greater than the position of the left-hand side of the button (x position). 
	The mouse y position is the same logic as with the mouse x position, but using GetY function and height. */
	if (mousePos->GetX() < (position.GetX() + width)
		&& mousePos->GetX() > position.GetX()
		&& mousePos->GetY() < (position.GetY() + height)
		&& mousePos->GetY() > position.GetY())
	{
		// Mouse has hovered over the button and set the current frame to MOUSE_OVER enumeration type
		currentFrame = MOUSE_OVER;

		// If the left mouse is clicked on the button, set the current frame to the CLICKED enumeration type
		if (TheInputHandler::InputHandlerInstance()->GetMouseButtonState(LEFT_MOUSE_BUTTON) && released)
		{
			currentFrame = CLICKED;

			if (callbackFunction != 0)
			{
				callbackFunction();
			}

			released = false;
		}

		else if (!TheInputHandler::InputHandlerInstance()->GetMouseButtonState(LEFT_MOUSE_BUTTON))
		{
			released = true;

			currentFrame = MOUSE_OVER;
		}
	}

	// Else if the mouse is outside of the button, set the current frame back to MOUSE_OUT
	else
	{
		currentFrame = MOUSE_OUT;
	}
}

void MenuButton::Clean()
{
	ShooterObject::Clean();
}

void MenuButton::LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_)
{
	ShooterObject::LoadGameObject(loaderParams_);

	callbackID = loaderParams_->GetCallbackID();
	currentFrame = MOUSE_OUT;
}

int MenuButton::GetCallbackID()
{
	return callbackID;
}

void MenuButton::SetCallback(void(*callback_)())
{
	callbackFunction = callback_;
}
