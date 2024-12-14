#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Windows.h>

#include "TextureManager.h"

using namespace std;

class Window
{
public:
	Window();
	~Window();

	bool InitializeSDL(const char* title, int x, int y, int width, int height, bool fullscreen);
	void RenderSDL();
	void HandleEvents();
	void ViewCoutMessages();
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;

	bool isRunning;
	int flags;

	int currentFrame;

	typedef TextureManager TheTextureManager;
};

#endif /* defined(WINDOW_H) */