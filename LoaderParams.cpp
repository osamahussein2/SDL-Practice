#include "LoaderParams.h"

LoaderParams::LoaderParams(int x_, int y_, int width_, int height_, string textureID_, int numberOfFrames_, 
	int callbackID_, int animationSpeed_) : x(x_), y(y_), width(width_), height(height_), textureID(textureID_), 
	numberOfFrames(numberOfFrames_), callbackID(callbackID_), animationSpeed(animationSpeed_)
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

int LoaderParams::GetNumberOfFrames() const
{
	return numberOfFrames;
}

int LoaderParams::GetCallbackID() const
{
	return callbackID;
}

int LoaderParams::GetAnimationSpeed() const
{
	return animationSpeed;
}
