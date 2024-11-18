#include "Window.h"

Window::Window()
{
	gameWindow = 0;
	gameRenderer = 0;
}

// Use this deconstructor to tell SDL when we should close the window by itself
Window::~Window()
{
	gameWindow = 0;
	gameRenderer = 0;
}

int Window::InitializeSDL(const char* title, int x, int y, int width, int height, Uint32 flags)
{
	// Initialize SDL to initialize all of the SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		gameWindow = SDL_CreateWindow(title, x, y, width, height, flags);

		// Create an SDL renderer if the window creation works
		if (gameWindow != 0)
		{
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
		}
	}

	else if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		// If the game window is less than 0, return 1 to indicate that SDL can't be initialized
		return 1;
	}

	/* When everything in SDL works, draw the window.
	SDL_SetRenderDrawColor function passes in an SDL_Renderer*, a red value, green value, blue value, and the alpha value (transparent-opaque). */

	// Make the SDL window black
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);

	// Clear the window to black
	SDL_RenderClear(gameRenderer);

	// Show the SDL window render drawing
	SDL_RenderPresent(gameRenderer);

	// Wait for a certain amount of milliseconds using SDL_Delay function
	SDL_Delay(5000);

	// Quit SDL after we reached the delay value above 
	SDL_Quit();

	return 0;
}