#include "PlayGame.h"



void PlayGame(const int& n, SDL_Event& e, bool& quit) {
	if (n == 15) {
		Text click_start;
		if (!click_start.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		click_start.SetText("click to play");
		click_start.SetColor(black);

		Text eachMove;
		if (!eachMove.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		eachMove.SetText("45s for each move");
		eachMove.SetColor(black);

		Game game;
		game.SetN(15);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		game.RenderRunningstate();
		eachMove.RenderText(137, 350);
		click_start.RenderText(175, 375);
		
		SDL_RenderPresent(gRenderer);

		bool isBreak = false;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
					break;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN) {
					isBreak = true;
					break;
				}
			}
			if (isBreak) break;
		}

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();

		game.logic(e, quit);
	}
	else {
		Text click_start;
		if (!click_start.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		click_start.SetText("click to play");
		click_start.SetColor(black);

		Text eachMove;
		if (!eachMove.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		eachMove.SetText("45s for each move");
		eachMove.SetColor(black);

		Game3x3 game;
		game.SetN(3);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		game.RenderRunningstate();

		eachMove.RenderText(137, 350);
		click_start.RenderText(175, 375);

		SDL_RenderPresent(gRenderer);

		bool isBreak = false;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
					break;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN) {
					isBreak = true;
					break;
				}
			}
			if (isBreak) break;
		}

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();

		game.logic(e, quit);
	}
}

void PlayGameBot(const int& n, SDL_Event& e, bool& quit) {
	if (n == 3) {
		Text click_start;
		if (!click_start.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		click_start.SetText("click to play");
		click_start.SetColor(black);

		Text eachMove;
		if (!eachMove.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		eachMove.SetText("45s for each move");
		eachMove.SetColor(black);


		Game3x3bot game;
		game.SetN(3);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		game.RenderRunningstate();

		eachMove.RenderText(137, 350);
		click_start.RenderText(175, 375);

		SDL_RenderPresent(gRenderer);

		bool isBreak = false;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
					break;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN) {
					isBreak = true;
					break;
				}
			}
			if (isBreak) break;
		}

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();

		game.logic(e, quit);
	}
	else {
		Text click_start;
		if (!click_start.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		click_start.SetText("click to play");
		click_start.SetColor(black);

		Text eachMove;
		if (!eachMove.OpenFont(17, "img/gamecuben.ttf")) {
			std::cout << SDL_GetError();
			return;
		}
		eachMove.SetText("45s for each move");
		eachMove.SetColor(black);


		Game15x15bot game;
		game.SetN(15);
		game.InitBoard();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();

		eachMove.RenderText(137, 350);
		click_start.RenderText(175, 375);

		SDL_RenderPresent(gRenderer);

		bool isBreak = false;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
					break;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN) {
					isBreak = true;
					break;
				}
			}
			if (isBreak) break;
		}

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		game.RenderRunningstate();

		game.logic(e, quit);
	}
	
}