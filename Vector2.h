#pragma once

#include <math.h>

class Vector2
{
public:
	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float x_, float y_);

	float GetX();
	float GetY();

	void SetX(float x_);
	void SetY(float y_);

	float length();

	Vector2 operator+(const Vector2& vec2_) const;
	friend Vector2& operator+=(Vector2& vec1_, const Vector2& vec2_);

	Vector2 operator-(const Vector2& vec2_) const;
	friend Vector2& operator-=(Vector2& vec1_, const Vector2& vec2_);

	Vector2 operator*(float scalarNumber_);
	Vector2& operator*=(float scalarNumber_);

	Vector2 operator/(float scalarNumber_);
	Vector2& operator/=(float scalarNumber_);

	void Normalize();

	float x, y;
};