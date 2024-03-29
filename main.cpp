
#include "menu1.h"
#include "menu2.h"
#include "game.h" 
#include "playgame.h"
#include "choosetictactoe.h"


int main(int argc, char* argv[])
{
	Text start, out;
	Text returnMenu1, goToTictactoe, goTo5x5, goTo15x15, PlayWithBot, Solo;

	if (!Init()) {
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	
	SDL_Event e;
	bool quit = false;
	

	while (!quit) {
		switch (menutype) {
		case STARTMENU:
			SDL_RenderClear(gRenderer);
			RenderMenu1(start, out);
			SDL_RenderPresent(gRenderer);
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) quit = true;
				else if (e.type == SDL_MOUSEBUTTONUP) {
					if (CheckClick(*start.GetRect(), e.button.x, e.button.y)) menutype = CHOOSEMAP;
					else if (CheckClick(*out.GetRect(), e.button.x, e.button.y)) quit = true;
				}
			}
			break;
		case CHOOSEMAP:
			SDL_SetRenderDrawColor(gRenderer, 0, 100, 255, 0);
			SDL_RenderClear(gRenderer);
			RenderMenu2(returnMenu1, goToTictactoe, goTo5x5, goTo15x15, white, white, white, white);
			SDL_RenderPresent(gRenderer);
			CheckClickMenu2(e, quit, returnMenu1, goToTictactoe, goTo5x5, goTo15x15);
			break;
		case CHOOSETICTACTOE:
			SDL_RenderClear(gRenderer);
			RenderChooseTictactoe(goToTictactoe, PlayWithBot, Solo);
			CheckChooseTictactoe(e, quit, goToTictactoe, PlayWithBot, Solo);
			SDL_RenderPresent(gRenderer);
			break;
		case PLAY15X15:
			PlayGame(15, e, quit);
			break;
		case PLAY5X5:
			PlayGame(5, e, quit);
			break;
		case PLAYTICTACTOE:
			PlayGame(3, e, quit);
			break;
		}
	}
	Close();
	return 0;
}






