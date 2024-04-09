#include "PlayGame.h"

void PlayGame(const int& n, SDL_Event& e, bool& quit) {
	if (n == 15) {
		Game game;
		game.SetN(15);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate(-1, -1);

		Text click;
		if (!click.OpenFont(20, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		click.SetColor(black);
		click.SetText("click to play");
		click.RenderText(70, 400);

		SDL_RenderPresent(gRenderer);
		game.HandleBeforeMenu(e, quit);
	}
	else {
		Game3x3 game;
		game.SetN(3);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate(-1, -1);

		Text click;
		if (!click.OpenFont(20, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		click.SetColor(black);
		click.SetText("click to play");
		click.RenderText(70, 400);

		SDL_RenderPresent(gRenderer);
		game.HandleBeforeMenu(e, quit);
	}
}

