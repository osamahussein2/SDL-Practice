#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <array>
#include <Windows.h>

#include "GameObject.h"
#include "TextureManager.h"

using namespace std;

class Window
{
public:
	~Window();
	
	static Window* WindowInstance();

	bool InitializeSDL(const char* title, int x, int y, int width, int height, bool fullscreen);
	SDL_Renderer* GetRenderer() const;
	void DrawObjects();
	void UpdateObjects();
	void RenderSDL();
	void HandleEvents();
	void ViewCoutMessages();
private:
	Window();

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;

	bool isRunning;
	int flags;

	int currentFrame;

	typedef TextureManager TheTextureManager;

	vector<GameObject*> gameObjects;

	static Window* windowInstance;
};

#endif /* defined(WINDOW_H) */