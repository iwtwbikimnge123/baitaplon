#include "StartMenu.h"

int main(int argc, char* argv[])
{
	if (!Init()) {
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Rect rect = { 150, 450, 200, 110 };
	SDL_Rect rectbasep = { 100, 370, 300, 60 };
	SDL_Rect rectbases = { 100, 300, 300, 60 };

	SDL_Rect rect2 = { 105, 375, 145, 50 };
	SDL_Rect rect3 = { 250, 375, 145, 50 };

	SDL_Event e;
	bool quit = false;

	MenuStart menuStart;

	while (!quit) {
		menuStart.HandleEvent(e, quit);
	}

	Close();
	return 0;
}






