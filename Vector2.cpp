#include "Vector2.h"

Vector2::Vector2(float x_, float y_) : x(x_), y(y_)
{
}

float Vector2::GetX()
{
	return x;
}

float Vector2::GetY()
{
	return y;
}

void Vector2::SetX(float x_)
{
	x = x_;
}

void Vector2::SetY(float y_)
{
	y = y_;
}

float Vector2::length()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::operator+(const Vector2& vec2_) const
{
	return Vector2(x + vec2_.x, y + vec2_.y);
}

Vector2& operator+=(Vector2& vec1_, const Vector2& vec2_)
{
	vec1_.x += vec2_.x;
	vec1_.y += vec2_.y;

	return vec1_;
}

Vector2 Vector2::operator-(const Vector2& vec2_) const
{
	return Vector2(x - vec2_.x, y - vec2_.y);
}

Vector2& operator-=(Vector2& vec1_, const Vector2& vec2_)
{
	vec1_.x -= vec2_.x;
	vec1_.y -= vec2_.y;

	return vec1_;
}

Vector2 Vector2::operator*(float scalarNumber_)
{
	return Vector2(x * scalarNumber_, y * scalarNumber_);
}

Vector2& Vector2::operator*=(float scalarNumber_)
{
	x *= scalarNumber_;
	y *= scalarNumber_;

	return *this;
}

Vector2 Vector2::operator/(float scalarNumber_)
{
	return Vector2(x / scalarNumber_, y / scalarNumber_);
}

Vector2& Vector2::operator/=(float scalarNumber_)
{
	x /= scalarNumber_;
	y /= scalarNumber_;

	return *this;
}

void Vector2::Normalize()
{
	float l = length();

	// Never attempt to divide by 0 by making sure the length is always greater than 0
	if (l > 0)
	{
		*this *= 1 / 1;
	}
}