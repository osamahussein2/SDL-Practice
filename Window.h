#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <iostream>

using namespace std;

class Window
{
public:
	Window();
	~Window();

	bool InitializeSDL(const char* title, int x, int y, int width, int height, Uint32 flags);
	void RenderSDL();
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	bool isRunning;
};

#endif /* defined(WINDOW_H) */