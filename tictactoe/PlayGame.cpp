#include "PlayGame.h"


void PlayGame(const int& n, SDL_Event& e, bool& quit) {
	if (n == 15) {
		Game game;
		game.SetN(15);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();
		game.logic(e, quit);
	}
	else {
		Game3x3 game;
		game.SetN(3);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();
		game.logic(e, quit);
	}
}

void PlayGameBot(const int& n, SDL_Event& e, bool& quit) {
	if (n == 3) {
		Game3x3bot game;
		game.SetN(3);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();
		game.logic(e, quit);
	}
	/*
	else {
		Game15x15bot game;
		game.SetN(15);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();
		game.logic(e, quit);
	}
	*/
}