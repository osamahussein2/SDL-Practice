#include "Window.h"

int main(int argc, char* args[])
{
	TheWindow::WindowInstance()->InitializeSDL("SDL Practice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 
		480, false);

	TheWindow::WindowInstance()->RenderSDL();

	return 0;
}