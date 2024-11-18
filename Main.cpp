#include "Window.h"

int main(int argc, char* args[])
{
	Window window = Window();

	window.InitializeSDL("SDL Practice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	window.~Window();

	return 0;
}