#include "Camera.h"
#include "Window.h"

Camera* Camera::cameraInstance = new Camera();

Camera::Camera() : target(0), position(0, 0)
{
}

Camera::~Camera()
{
	delete target;
}

void Camera::Update(Vector2 velocity_)
{
	position += velocity_;

	if (position.x < 0)
	{
		position.x = 0;
	}
}

void Camera::SetTarget(Vector2* target_)
{
	target = target_;
}

const Vector2 Camera::GetPosition() const
{
	if (target != 0)
	{
		// Move the map and decide which tiles to draw
		Vector2 pos(target->x - (TheWindow::WindowInstance()->GetWindowWidth() / 2), 0);

		if (pos.x < 0)
		{
			pos.x = 0;
		}

		return pos;
	}

	return position;
}

void Camera::SetPosition(const Vector2& position_)
{
	position = position_;
}