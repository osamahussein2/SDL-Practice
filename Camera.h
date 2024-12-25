#pragma once

#include "Vector2.h"

class Camera
{
public:
	static Camera* CameraInstance()
	{
		if (cameraInstance == 0)
		{
			cameraInstance = new Camera();

			return cameraInstance;
		}

		return cameraInstance;
	}

	void Update(Vector2 velocity_);

	void SetTarget(Vector2* target_);

	const Vector2 GetPosition() const;
	void SetPosition(const Vector2& position_);

private:
	Camera();
	~Camera();

	// Camera's target and position
	Vector2* target;
	Vector2 position;

	static Camera* cameraInstance;
};

typedef Camera TheCamera;