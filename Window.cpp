#include "Window.h"
#include "Player.h"
#include "Enemy.h"

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

// Define the static instance
Window* Window::windowInstance = 0;

typedef InputHandler TheInputHandler;

Window::Window()
{
	gameWindow = 0;
	gameRenderer = 0;

	isRunning = false;
	flags = 0;

	currentFrame = 0;

	delayTime = 1000.0f / FPS;

	frameStart = 0;
	frameTime = 0;
}

// Use this deconstructor to tell SDL when we should close the window by itself
Window::~Window()
{
	flags = 0;

	currentFrame = 0;
}

Window* Window::WindowInstance()
{
	if (windowInstance == 0)
	{
		windowInstance = new Window();
		return windowInstance;
	}

	return windowInstance;
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

				TheInputHandler::InputHandlerInstance()->InitializeJoysticks();

				// Load the texture before loading the game objects
				TheTextureManager::TextureManagerInstance()->LoadTexture("Sprites/Animate-alpha.png",
					"Animate", gameRenderer);

				gameObjects.push_back(new Player(new LoaderParams(100, 100, 100, 82, "Animate")));
				gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 100, 82, "Animate")));
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

SDL_Renderer* Window::GetRenderer() const
{
	return gameRenderer;
}

void Window::DrawObjects()
{
	/* In other words, a virtual function would always call the draw function contained in GameObject, neither Player
	nor Enemy. We would never have the overriden behavior we want. The virtual keyword would ensure the Player and Enemy
	draw fucntions are called (go to GameObject.h file to see the virtual functions) */

	// Loop through all the objects we initialized and draw them
	for (vector<GameObject*>::size_type i = 0; i != gameObjects.size(); i++)
	{
		gameObjects[i]->Draw();
	}
}

void Window::UpdateObjects()
{
	// Loop through all the objects we initialized and update them
	for (vector<GameObject*>::size_type i = 0; i != gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

void Window::RenderSDL()
{
	// While isRunning is set to true, render the window for us until we decide to quit the program
	while (isRunning != false)
	{
		// Call the viewing console messages function while SDL is running (optional, mainly used for testing purposes)
		//ViewCoutMessages();

		// Get the amount of milliseconds since SDL was initialized for frame start
		frameStart = SDL_GetTicks();

		// Call the handle events function whenever SDL window is running
		HandleEvents();

		// Clear the window with the set drawing color
		SDL_RenderClear(gameRenderer);

		DrawObjects();
		UpdateObjects();

		// Store how long the running loop took to run by subtracting the time our frame started from the current time
		frameTime = SDL_GetTicks() - frameStart;

		/* If the frame time is less than the time we want the frame to take (delay time), call SDL_Delay and make
		our loop wait for the amount of time we want it to, subtracting how long the loop already took to complete */
		if (frameTime < delayTime)
		{
			// Add delay to slow down any movement in the window
			SDL_Delay(static_cast<int>(delayTime - frameTime));
		}

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

		// Clean the window up after SDL quits
		Window::~Window();
		TheTextureManager::TextureManagerInstance()->~TextureManager();
		TheInputHandler::InputHandlerInstance()->CleanInputHandler();

		// Quit SDL when isRunning returns false
		SDL_Quit();
	}
}

void Window::HandleEvents()
{
	TheInputHandler::InputHandlerInstance()->UpdateInputHandler();
}

void Window::ViewCoutMessages()
{
	// To enable viewing std::cout messages to the console, include <Windows.h>
	// Then, call AllocConsole() function and andfreopen("CON", "w", stdout)
	AllocConsole();
	freopen("CON", "w", stdout);
}
