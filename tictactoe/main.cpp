#include "StartMenu.h"
#include "PlayGame.h"

int main(int argc, char* argv[])
{
	if (!Init()) {
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Event e;
	bool quit = false;

	MenuStart menuStart;

	while (!quit) {
		switch (menuType) {
		case STARTMENU:
			menuStart.HandleEvent(e, quit);
			break;
		case PLAY15X15_2PLAYER:
			PlayGame(15, e, quit);
			menuStart.RestartMenu();
			break;
		case PLAY3x3_2PLAYER:
			PlayGame(3, e, quit);
			menuStart.RestartMenu();
			break;
		}
		
	}

	Close();
	return 0;
}






