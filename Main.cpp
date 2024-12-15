#include "Window.h"

typedef Window Game;

int main(int argc, char* args[])
{
	Game::WindowInstance()->InitializeSDL("SDL Practice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);
	Game::WindowInstance()->RenderSDL();

	return 0;
}