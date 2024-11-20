#include "Window.h"

/* SDL initialization flags:

	SDL_INIT_HAPTIC - force feedback SDL system
	SDL_INIT_AUDIO - audio SDL system
	SDL_INIT_VIDEO - video SDL system
	SDL_INIT_TIMER - timer SDL system
	SDL_INIT_JOYSTICK - joystick SDL system
	SDL_INIT_EVEYRTHING - all SDL system
	SDL_INIT_NOPARACHUTE - don't catch fatal signals

	Bitwise operator can be used to initialize more than 1 SDL subsystem (e.g. SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	To check whether a subsystem is initialized or not, we can use SDL_WasInit() function:

		if (SDL_WasInit(SDL_INIT_VIDEO) != 0)
		{
			cout << "Video was initialized";
		}

*/

/* SDL renderer flags (when initializing the SDL_Renderer flag):

	SDL_RENDERER_SOFTWARE - use software rendering
	SDL_RENDERER_ACCELERATED - use hardware acceleration
	SDL_RENDERER_PRESENTVSYNC - synchronize renderer update with screen's refresh rate
	SDL_RENDERER_TARGETTEXTURE - supports render to texture

*/

Window::Window()
{
	gameWindow = 0;
	gameRenderer = 0;

	isRunning = false;
}

// Use this deconstructor to tell SDL when we should close the window by itself
Window::~Window()
{
	gameWindow = 0;
	gameRenderer = 0;

	isRunning = false;
}

bool Window::InitializeSDL(const char* title, int x, int y, int width, int height, Uint32 flags)
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
		
		// Set isRunning to true after the SDL window and render creation
		isRunning = true;
	}

	else if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		// If the game window is less than 0, set isRunning to false to indicate that SDL can't be initialized
		isRunning = false;
	}

	// Return the isRunning boolean for us
	return isRunning;
}

void Window::RenderSDL()
{
	// While isRunning is set to true, render the window for us until we decide to quit the program
	while (isRunning != false)
	{
		/* When everything in SDL works, draw the window.
		SDL_SetRenderDrawColor function passes in an SDL_Renderer*, a red value, green value, blue value, and the alpha value (transparent-opaque). */

		// Make the SDL window black
		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);

		// Clear the window to black
		SDL_RenderClear(gameRenderer);

		// Show the SDL window render drawing
		SDL_RenderPresent(gameRenderer);
	}

	/* Wait for a certain amount of milliseconds using SDL_Delay function
	SDL_Delay(5000); this is useless now that I set up the isRunning boolean */

	if (isRunning != true)
	{
		// Quit SDL when isRunning returns false
		SDL_Quit();
	}
}
