#pragma once

#include <string>

using namespace std;

/* LoaderParams is a class that takes values into its constructor and sets them as member variables that can then be
accessed to set the initial values of an object */

class LoaderParams
{
public:
	LoaderParams(int x_, int y_, int width_, int height_, string textureID_);

	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;

	string GetTextureID() const;

private:
	int x, y;

	int width, height;

	string textureID;
};