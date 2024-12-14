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

/* Table of SDL_WindowFlags function:

	SDL_WINDOW_FULLSCREEN - make the window fullscreen
	SDL_WINDOW_OPENGL - window can be used with as an OpenGL context
	SDL_WINDOW_SHOWN - the window is visible
	SDL_WINDOW_HIDDEN - hide the window
	SDL_WINDOW_BORDERLESS - no border on the window
	SDL_WINDOW_RESIZABLE - enable resizing of the window
	SDL_WINDOW_MINIMIZED - minimize the window
	SDL_WINDOW_MAXIMIZED - maximize the window
	SDL_WINDOW_INPUT_GRABBED - window has grabbed input focus
	SDL_WINDOW_INPUT_FOCUS - window has input focus
	SDL_WINDOW_MOUSE_FOCUS - window has mouse focus
	SDL_WINDOW_FOREIGN - the window was not created using SDL

*/

/*
	The available values for the SDL_RendererFlip enumerated type include:

	SDL_FLIP_NONE - no flipping
	SDL_FLIP_HORIZONTAL - flip the texture horizontally
	SDL_FLIP_VERTICAL - flip the texture vertically

*/

Window::Window()
{
	gameWindow = 0;
	gameRenderer = 0;

	isRunning = false;
	flags = 0;

	currentFrame = 0;
}

// Use this deconstructor to tell SDL when we should close the window by itself
Window::~Window()
{
	gameWindow = 0;
	gameRenderer = 0;

	isRunning = false;

	flags = 0;

	currentFrame = 0;
}

bool Window::InitializeSDL(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	// Initialize SDL to initialize all of the SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// If full screen is set to false, don't make the window fullscreen then
		if (!fullscreen)
		{
			flags = 0;
		}

		// If full screen is set to true, make the window fullscreen
		else if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		gameWindow = SDL_CreateWindow(title, x, y, width, height, fullscreen);

		// Create an SDL renderer if the window creation works
		if (gameWindow != 0)
		{
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);

			// If the game renderer is successful
			if (gameRenderer != 0)
			{
				/* When everything in SDL works, draw the window.

				SDL_SetRenderDrawColor function passes in an SDL_Renderer*, a red value, green value, blue value,
				and the alpha value (transparent-opaque). */

				// Make the SDL window red
				SDL_SetRenderDrawColor(gameRenderer, 255, 0, 0, 255);

				TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Animate-alpha.png", 
					"Animate", gameRenderer);
			}

			else
			{
				// If the game renderer fails to initialize, set isRunning to false to close SDL immediately
				isRunning = false;
			}
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
		// Call the viewing console messages function while SDL is running (optional, mainly used for testing purposes)
		//ViewCoutMessages();

		// Call the handle events function whenever SDL window is running
		HandleEvents();

		// Clear the window with the set drawing color
		SDL_RenderClear(gameRenderer);

		/* SDL_GetTicks gets the amount of time in milliseconds since SDL was initialized. Then, I divided it by
		the amount of frames I want the animation to update and used the modulo (%) operator to keep it in range of
		the amount of the animation frames in the sprite sheet */
		currentFrame = static_cast<int>((SDL_GetTicks() / 100) % 6);

		TheTextureManager::TextureManagerInstance()->DrawTexture("Animate", 0, 0, 100, 82, gameRenderer, SDL_FLIP_NONE);
		TheTextureManager::TextureManagerInstance()->DrawFrame("Animate", 100, 100, 100, 82, 0, currentFrame, 
			gameRenderer, SDL_FLIP_NONE);

		// Show the SDL window render drawing
		SDL_RenderPresent(gameRenderer);
	}

	/* Wait for a certain amount of milliseconds using SDL_Delay function
	SDL_Delay(5000); this is useless now that I set up the isRunning boolean */

	if (isRunning != true)
	{
		// Destroy both the window and renderer once isRunning is false
		SDL_DestroyWindow(gameWindow);
		SDL_DestroyRenderer(gameRenderer);

		TheTextureManager::TextureManagerInstance()->~TextureManager();

		// Quit SDL when isRunning returns false
		SDL_Quit();
	}
}

void Window::HandleEvents()
{
	SDL_Event event;

	// Check if there's an event to handle
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		// SDL_QUIT event occurs when the mouse clicks on a red cross in the window
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
		}
	}
}

void Window::ViewCoutMessages()
{
	// To enable viewing std::cout messages to the console, include <Windows.h>
	// Then, call AllocConsole() function and andfreopen("CON", "w", stdout)
	AllocConsole();
	freopen("CON", "w", stdout);
}
