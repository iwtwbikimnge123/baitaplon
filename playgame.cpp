#pragma once
#include "playgame.h"

void PlayGame(const int & n, SDL_Event& e, bool& quit) {
	if (n != 3) {
		Game game;
		game.SetN(n);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.DrawGrid();
		SDL_RenderPresent(gRenderer);
		game.logic(e, quit);
	}
	else {
		GameTictactoe game;
		game.SetN(n);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.DrawGrid();
		SDL_RenderPresent(gRenderer);
		game.logic(e, quit);
	}
}