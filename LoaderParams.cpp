#include "LoaderParams.h"

LoaderParams::LoaderParams(int x_, int y_, int width_, int height_, string textureID_) : x(x_), y(y_), width(width_),
height(height_), textureID(textureID_)
{
}

int LoaderParams::GetX() const
{
	return x;
}

int LoaderParams::GetY() const
{
	return y;
}

int LoaderParams::GetWidth() const
{
	return width;
}

int LoaderParams::GetHeight() const
{
	return height;
}

string LoaderParams::GetTextureID() const
{
	return textureID;
}