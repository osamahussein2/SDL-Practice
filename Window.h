#pragma once

#include <SDL.h>
#include <iostream>

using namespace std;

class Window
{
public:
	Window();
	~Window();

	int InitializeSDL(const char* title, int x, int y, int width, int height, Uint32 flags);
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
};