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
#include "InputHandler.h"
#include "GameStateMachine.h"

using namespace std;

class Window
{
public:
	static Window* WindowInstance();

	bool InitializeSDL(const char* title, int x, int y, int width, int height, bool fullscreen);
	SDL_Renderer* GetRenderer() const;
	void Draw();
	void Update();
	void RenderSDL();
	void HandleEvents();
	void ViewCoutMessages();
	GameStateMachine* GetGameStateMachine();

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	int GetPlayerLives();
	void SetPlayerLives(int playerLives_);

	int GetCurrentLevel();
	void SetCurrentLevel(int currentLevel_);

	const int GetNextLevel();
	void SetNextLevel(int nextLevel_);

	bool GetLevelComplete();
	void SetLevelComplete(bool levelComplete_);

	float GetScrollSpeed();

	bool ChangingState();
	void ChangingState(bool chaningState_);

	vector<string> GetLevelFiles();

	bool isRunning;
private:
	Window();
	~Window();

	Window(const Window&);
	Window& operator=(const Window&);

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;

	int flags;

	int currentFrame;

	float scrollSpeed;

	int playerLives;

	vector<GameObject*> gameObjects;

	static Window* windowInstance;

	const int FPS = 60;
	int delayTime;

	Uint32 frameStart, frameTime;

	GameStateMachine* gameStateMachine;

	int windowWidth, windowHeight;
	int currentLevel, nextLevel;

	bool levelComplete;

	vector<string> levelFiles;

	bool changingState;
};

typedef Window TheWindow;

#endif /* defined(WINDOW_H) */