#pragma once

#include <string>

using namespace std;

/* LoaderParams is a class that takes values into its constructor and sets them as member variables that can then be
accessed to set the initial values of an object */

class LoaderParams
{
public:
	LoaderParams(int x_, int y_, int width_, int height_, string textureID_, int numberOfFrames_, int callbackID_ = 0,
		int animationSpeed_ = 0);

	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;

	string GetTextureID() const;
	int GetNumberOfFrames() const;
	int GetCallbackID() const;
	int GetAnimationSpeed() const;

private:
	int x, y;

	int width, height;
	int numberOfFrames;

	string textureID;

	int callbackID;
	int animationSpeed;
};