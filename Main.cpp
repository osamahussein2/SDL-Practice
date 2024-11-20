#include "Window.h"

Window* window = nullptr;

int main(int argc, char* args[])
{
	window = new Window();

	window->InitializeSDL("SDL Practice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	window->RenderSDL();

	// Clean the window up after SDL quits
	window->~Window();

	return 0;
}